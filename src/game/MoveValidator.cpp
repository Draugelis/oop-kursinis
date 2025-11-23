#include "MoveValidator.h"
#include "bitboards/AttackGenerator.h"
#include "core/Logging.h"
#include "game/Board.h"
#include "game/MoveType.h"

namespace game {

/**
 * @brief Find color's king position
 *
 * @param color Player's color
 * @return core::Position King's position
 */
core::Position MoveValidator::findKing(core::Color color) const {
  bitboards::BitBoard kingBitBoard =
      m_bitboards.getPieceBitBoard(color, core::PieceType::KING);
  // There can be only one king so first bit will suffice
  return kingBitBoard.getFirstSetBit();
}

/**
 * @brief Check if move results in leaving king in a check position
 *
 * leavesKingInCheck temporary makes a move and checks if king is in check and
 * then restores board to the previous state
 *
 * @param move Move to evaluate
 * @param context Move context
 * @return true If move leaves king in check (illegal move)
 * @return false If move doesn't leave king in check
 */
bool MoveValidator::leavesKingInCheck(const Move &move,
                                      const MoveContext &context) const {
  Logger::FunctionScope logScope;

  Logger::debug(moveDebug(), "Testing if move leaves king exposed");

  core::Color color = context.getSideToMove();
  core::Color opponentColor = color.opposite();

  // Save captured piece information for restoration
  std::optional<core::PieceType> capturedPieceType = std::nullopt;
  std::optional<core::Position> capturePiecePosition = std::nullopt;

  // Temporary board adapter for simple piece type fetching
  Board board(m_bitboards);
  if (move.isCapture()) {
    capturePiecePosition = move.getTo();
    auto capturedPiece = board.getPieceAt(*capturePiecePosition);
    if (capturedPiece) {
      capturedPieceType = capturedPiece->getType();
      Logger::debug(moveDebug(),
                    "Capturing " +
                        std::string(1, capturedPiece->getColor().toLetter()) +
                        std::string(1, capturedPiece->getLetter()));
    }
  }
  // Of course, en passant is a special case
  if (move.isEnPassant()) {
    // Calculate where is the piece captured with en passant
    int direction = color == core::Color::WHITE ? 1 : -1;
    core::Position destination = move.getTo();
    // Captured piece will be in the opposite rank of the movement direction so
    // using subtraction
    capturePiecePosition = core::Position(destination.getRank() - direction,
                                          destination.getFile());

    auto capturedPiece = board.getPieceAt(*capturePiecePosition);
    if (capturedPiece) {
      capturedPieceType = capturedPiece->getType();
    }
    // Remove captured piece
    board.removePiece(*capturePiecePosition);
  }

  // Apply move
  m_bitboards.movePiece(move.getFrom(), move.getTo(), color,
                        move.getPieceType());

  // Create new context with new occupancy for the evaluation
  bitboards::BitBoard intermediateOccupancy = m_bitboards.getAllOccupancy();
  MoveContext intermediateContext(
      context.getCastlingRights(), context.getEnPassant(),
      context.getSideToMove(), intermediateOccupancy);

  // Evaluate if king is in check after the move
  bool leftInCheck = isInCheck(color, intermediateContext);

  Logger::debug(moveDebug(),
                "King in check after move: " + std::to_string(leftInCheck));

  // Move piece back
  m_bitboards.movePiece(move.getTo(), move.getFrom(), color,
                        move.getPieceType());

  // Place captured piece back
  if (capturedPieceType.has_value() && capturePiecePosition.has_value()) {
    m_bitboards.setPiece(capturePiecePosition.value(), opponentColor,
                         capturedPieceType.value());
  }

  return leftInCheck;
}

/**
 * @brief Check if castling is legal.
 *
 * It is illegal to castle from/to/through check position
 *
 * @see Castling rules:
 * https://www.chess.com/article/view/how-to-castle-in-chess
 * @param move Move to evaluate
 * @param context Move context
 * @return true If castling is legal
 * @return false If casling is illegal
 */
bool MoveValidator::isCastleLegal(const Move &move,
                                  const MoveContext &context) const {

  core::Color color = context.getSideToMove();

  // Check if castling rights exist for this move
  bool isKingside = (move.getType() == game::MoveType::CASTLE_KINGSIDE);
  bool isQueenside = (move.getType() == game::MoveType::CASTLE_QUEENSIDE);

  if (isKingside && !context.getCastlingRights().canCastleKingside(color)) {
    Logger::debug(moveDebug(), "Castling illegal: no kingside rights for " +
                                   color.toString());
    return false;
  }

  if (isQueenside && !context.getCastlingRights().canCastleQueenside(color)) {
    Logger::debug(moveDebug(), "Castling illegal: no queenside rights for " +
                                   color.toString());
    return false;
  }

  // Can't castle from check
  if (isInCheck(color, context)) {
    return false;
  }

  // Can't castle to check
  if (leavesKingInCheck(move, context)) {
    return false;
  }

  // Can't castle through check
  // Get a file between starting and destination files
  int passFile = (move.getFrom().getFile() + move.getTo().getFile()) / 2;
  int rank = move.getFrom().getRank();
  core::Position passPos(rank, passFile);
  if (isSquareAttacked(passPos, context)) {
    return false;
  }

  return true;
}

/**
 * @brief Remove illegal moves
 *
 * @param moves Vector of moves to filter
 * @param context Move context
 * @return std::vector<Move> Filtered moves
 */
std::vector<Move>
MoveValidator::filterLegalMoves(const std::vector<Move> &moves,
                                const MoveContext &context) const {
  Logger::FunctionScope logScope;

  Logger::debug(
      moveDebug(),
      "Filtering legal moves, input: " + std::to_string(moves.size()) +
          " pseudo-legal moves, side: " + context.getSideToMove().toString());

  // Get opponent's king position to prevent capturing it
  core::Color opponentColor = context.getSideToMove().opposite();
  core::Position opponentKingPos = findKing(opponentColor);

  std::vector<Move> legalMoves;
  // Simply check each move
  for (const Move &move : moves) {
    // King captures are never legal
    if (move.getTo() == opponentKingPos) {
      Logger::debug(moveDebug(),
                    "Filtered out king capture: " + move.toAlgebraic());
      continue;
    }

    if (isLegal(move, context)) {
      legalMoves.push_back(move);
    }
  }

  Logger::debug(moveDebug(), "Filtering complete, output: " +
                                 std::to_string(legalMoves.size()) +
                                 " legal moves");

  return legalMoves;
}

/**
 * @brief Check if the move is legal
 *
 * @param moves Vector of moves to filter
 * @param context Move context
 * @return true If move is legal
 * @return false If move is illegal
 */
bool MoveValidator::isLegal(const Move &move,
                            const MoveContext &context) const {
  Logger::FunctionScope logScope;

  Logger::debug(moveDebug(), "Checking legality: " + move.toAlgebraic());

  // Check if castling is legal
  if (move.isCastling()) {
    bool legal = isCastleLegal(move, context);
    Logger::debug(moveDebug(), "Castling legal: " + std::to_string(legal));
    return legal;
  }

  // Check if move doesn't leave king in check
  bool leavesInCheck = leavesKingInCheck(move, context);
  Logger::debug(moveDebug(),
                "Leaves king in check: " + std::to_string(leavesInCheck));

  return !leavesInCheck;
}

/**
 * @brief Check if a given color is currently in check
 *
 * @param color Color to check
 * @param context Move context
 * @return true If color is in check
 * @return false If color is not in cehck
 */
bool MoveValidator::isInCheck(core::Color color,
                              const MoveContext &context) const {
  // Just check whether king is currently attacked
  core::Position kingPos = findKing(color);
  return isSquareAttacked(kingPos, context);
}

/**
 * @brief Check if current player has legal moves
 *
 * @param moves Vector of moves
 * @param context Move context
 * @return true If player has legal moves
 * @return false If player doesn't have legal moves
 */
bool MoveValidator::hasLegalMoves(const std::vector<Move> &moves,
                                  const MoveContext &context) const {
  Logger::FunctionScope logScope;

  Logger::debug(moveDebug(), "Checking for legal moves, total: " +
                                 std::to_string(moves.size()));

  for (const Move &move : moves) {
    // Checking for at least one legal move
    if (isLegal(move, context)) {
      Logger::debug(moveDebug(), "Found legal move: " + move.toAlgebraic());

      return true;
    }
  }

  // No legal moves found
  Logger::debug(moveDebug(), "No legal moves found");
  return false;
}

/**
 * @brief Check if a given position is attacked by a color
 *
 * @param pos Position to check
 * @param context Move context
 * @return true If square is attacked by opponent
 * @return false If square isn't attacked by opponent
 */
bool MoveValidator::isSquareAttacked(const core::Position &pos,
                                     const MoveContext &context) const {
  // Opponent color
  core::Color enemyColor = context.getSideToMove().opposite();
  // Current board occupancy
  bitboards::BitBoard occupancy = context.getOccupancy();

  // Since attacks are symmetrical, we can check each piece type attacks from a
  // position and see if enemie's piece type is at the attack position

  // Check knight attacks
  bitboards::BitBoard knightAttacks = bitboards::AttackGenerator::getAttacks(
      core::PieceType::KNIGHT, pos, context.getSideToMove(), occupancy);

  // Check positions where enemy knights can attack current position
  bitboards::BitBoard knightAttackOverlap =
      (knightAttacks &
       m_bitboards.getPieceBitBoard(enemyColor, core::PieceType::KNIGHT));

  // Convert overlap to uint64_t
  // No overlap results in 0 value which is evaluates as false
  if (knightAttackOverlap.getBits()) {
    return true;
  }

  // Check bishop/queen attacks on diagonals
  bitboards::BitBoard bishopAttacks = bitboards::AttackGenerator::getAttacks(
      core::PieceType::BISHOP, pos, context.getSideToMove(), occupancy);

  // Check positions where enemy bishops or queens can attack current position
  bitboards::BitBoard bishopAttackOverlap =
      (bishopAttacks &
       (m_bitboards.getPieceBitBoard(enemyColor, core::PieceType::BISHOP) |
        m_bitboards.getPieceBitBoard(enemyColor, core::PieceType::QUEEN)));

  if (bishopAttackOverlap.getBits()) {
    return true;
  }

  // Check rook/queen attacks on cardinals
  bitboards::BitBoard rookAttacks = bitboards::AttackGenerator::getAttacks(
      core::PieceType::ROOK, pos, context.getSideToMove(), occupancy);

  // Check positions where enemy rooks or queens can attack current position
  bitboards::BitBoard rookAttackOverlap =
      (rookAttacks &
       (m_bitboards.getPieceBitBoard(enemyColor, core::PieceType::ROOK) |
        m_bitboards.getPieceBitBoard(enemyColor, core::PieceType::QUEEN)));

  if (rookAttackOverlap.getBits()) {
    return true;
  }

  // Check pawn attacks
  bitboards::BitBoard pawnAttacks = bitboards::AttackGenerator::getAttacks(
      core::PieceType::PAWN, pos, context.getSideToMove(), occupancy);

  // Check positions where enemy pawns can attack current position
  bitboards::BitBoard pawnAttackOverlap =
      (pawnAttacks &
       m_bitboards.getPieceBitBoard(enemyColor, core::PieceType::PAWN));

  if (pawnAttackOverlap.getBits()) {
    return true;
  }

  // Check for king attacks
  bitboards::BitBoard kingAttacks = bitboards::AttackGenerator::getAttacks(
      core::PieceType::KING, pos, context.getSideToMove(), occupancy);

  // Check positions where enemy king can attack current position
  bitboards::BitBoard kingAttackOverlap =
      (kingAttacks &
       m_bitboards.getPieceBitBoard(enemyColor, core::PieceType::KING));

  if (kingAttackOverlap.getBits()) {
    return true;
  }

  return false;
}

} // namespace game