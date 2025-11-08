#include "MoveGenerator.h"
#include "game/Board.h"

namespace game {

/**
 * @brief Generate pseudo legal moves for current color's pieces
 *
 * @param context Move context for additional details
 * @return std::vector<Move> Pseudo legal moves for all pieces
 */
std::vector<Move>
MoveGenerator::generateMoves(const MoveContext &context) const {
  std::vector<Move> moves;

  // Get current color's occupied tiles
  bitboards::BitBoard currentOccupancy =
      m_bitboards.getColorOccupancy(context.getSideToMove());
  // Get current occupancy positions
  std::vector<core::Position> currentPositions =
      currentOccupancy.getSetBitPositions();

  // Set up Board adapter
  Board board(m_bitboards);

  // Iterate through all positions
  for (core::Position pos : currentPositions) {
    // Get piece in the position
    auto piece = board.getPieceAt(pos);
    if (!piece)
      continue; // Skip if somehow there's no piece (shouldn't happen though)

    // Get all moves from the position
    std::vector<Move> pieceMoves = generatePieceMoves(pos, *piece, context);

    // Append moves vector with piece moves
    moves.insert(moves.end(), pieceMoves.begin(), pieceMoves.end());
  }

  return moves;
}

/**
 * @brief Generate pseudo legal moves for a piece
 *
 * Not accounting for check/checkmate and friendly-fire
 *
 * @param pos Piece's position
 * @param piece Piece to move
 * @param context Move context for additional details
 * @return std::vector<Move> Pseudo legal moves for a piece
 */
std::vector<Move>
MoveGenerator::generatePieceMoves(core::Position pos,
                                  const pieces::Piece &piece,
                                  const MoveContext &context) const {
  // Get current color
  core::Color color = context.getSideToMove();
  // retrieve move bitboards for a piece
  bitboards::BitBoard moveBitBoards = piece.getMoveBitBoard(pos, context);

  // Filter out moves/attacks on friendly pieces
  moveBitBoards &= ~m_bitboards.getColorOccupancy(color);

  // Calculate attack bitboards
  // capture will be where opponent occupies a move target
  bitboards::BitBoard captureBitBoards =
      moveBitBoards & m_bitboards.getColorOccupancy(color.opposite());

  // Remove captures from move tables
  moveBitBoards &= ~captureBitBoards;

  // Generate moves from bitboards
  std::vector<Move> moves;

  // Converting non-capture move bitboards
  for (core::Position moveDestination : moveBitBoards.getSetBitPositions()) {
    int destinationRank = moveDestination.getRank();
    int destinationFile = moveDestination.getFile();

    // Check for pawn promotion
    if (piece.getType() == core::PieceType::PAWN &&
        (destinationRank == core::RANK_8 || destinationRank == core::RANK_1)) {
      moves.push_back(Move(pos, moveDestination, piece.getType(), color,
                           MoveType::PROMOTION));
      continue; // Move added, carry on
    }

    // Check for castling
    if (piece.getType() == core::PieceType::KING) {
      bool isCastling =
          (destinationFile == core::FILE_G || destinationFile == core::FILE_C);

      if (isCastling) {
        MoveType castlingSide = destinationFile == core::FILE_G
                                    ? MoveType::CASTLE_KINGSIDE
                                    : MoveType::CASTLE_QUEENSIDE;
        moves.push_back(
            Move(pos, moveDestination, piece.getType(), color, castlingSide));
        continue; // Move added, carry on
      }
    }

    // Normal moves for non-promotions and non-castling
    moves.push_back(Move(pos, moveDestination, piece.getType(), color));
  }

  for (core::Position attackDestination :
       captureBitBoards.getSetBitPositions()) {
    int destinationRank = attackDestination.getRank();
    int destinationFile = attackDestination.getFile();

    // Check for pawn promotion captures
    if (piece.getType() == core::PieceType::PAWN &&
        (destinationRank == core::RANK_8 || destinationRank == core::RANK_1)) {
      moves.push_back(Move(pos, attackDestination, piece.getType(), color,
                           MoveType::PROMOTION_CAPTURE));
      continue; // Move added, carry on
    }

    // Normal capture if not promotion capture or en passant
    moves.push_back(Move(pos, attackDestination, piece.getType(), color,
                         MoveType::CAPTURE));
  }

  // Handling pawn en passant since it is a special case
  // En Passant is great
  // https://www.youtube.com/shorts/FzBMVgL1jbk
  if (piece.getType() == core::PieceType::PAWN &&
      context.getEnPassant().has_value()) {
    // epTarget - empty tile behind opponent pawn that double-pushed last turn
    core::Position epTarget = context.getEnPassant().value();

    int moveDirection = (color == core::Color::WHITE) ? 1 : -1;

    // Check if pawn is 1 diagonal away from epTarget
    if ((abs(pos.getFile() - epTarget.getFile()) == 1) &&
        (pos.getRank() + moveDirection == epTarget.getRank())) {
      moves.push_back(
          Move(pos, epTarget, piece.getType(), color, MoveType::EN_PASSANT));
    }
  }

  return moves;
}

} // namespace game
