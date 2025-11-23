#include "GameState.h"
#include "core/Logging.h"
#include <sstream>

namespace game {
/**
 * @brief Construct a new Game State object
 *
 */
GameState::GameState()
    : m_bitboards(),        // BitBoard Manager for bitboard interactions
      m_board(m_bitboards), // Adapter for UI layer querying the board
      m_moveGenerator(m_bitboards), // Psedo-legal move generator
      m_moveValidator(m_bitboards), // Move validation for filtering legal moves
      m_castlingRights(),           // Castling rights tracking
      m_enPassantTarget(std::nullopt),        // En Passant target position
      m_sideToMove(core::Color::WHITE),       // Current turn
      m_nHalfMoveClock(0),                    // Half move clock
      m_nFullMoveNumber(1),                   // Full move counter
      m_moveHistory(),                        // Move history tracking
      m_gameOutcome(GameOutcome::IN_PROGRESS) // Game just started
{
  loadFEN(core::DEFAULT_BOARD_FEN);
}

/**
 * @brief Construct a new Game State object with a custom FEN
 *
 */
GameState::GameState(const std::string &fen)
    : m_bitboards(),        // BitBoard Manager for bitboard interactions
      m_board(m_bitboards), // Adapter for UI layer querying the board
      m_moveGenerator(m_bitboards), // Psedo-legal move generator
      m_moveValidator(m_bitboards), // Move validation for filtering legal moves
      m_castlingRights(),           // Castling rights tracking
      m_enPassantTarget(std::nullopt),        // En Passant target position
      m_sideToMove(core::Color::WHITE),       // Current turn
      m_nHalfMoveClock(0),                    // Half move clock
      m_nFullMoveNumber(1),                   // Full move counter
      m_moveHistory(),                        // Move history tracking
      m_gameOutcome(GameOutcome::IN_PROGRESS) // Game just started
{
  loadFEN(fen);
}

/**
 * @brief Reset Game State to an initial default position
 *
 */
void GameState::reset() {
  m_moveHistory.clear();
  loadFEN(core::DEFAULT_BOARD_FEN);
}

/**
 * @brief Reset Game State to an initial position with FEN
 *
 */
void GameState::reset(const std::string &fen) {
  m_moveHistory.clear();
  loadFEN(fen);
}

/**
 * @brief Populate the board based on FEN
 *
 * @see FEN reference: https://www.chess.com/terms/fen-chess
 * @param fen Forsyth-Edwards Notation string
 */
void GameState::loadFEN(const std::string &fen) {
  // Clear out the board
  m_bitboards.clearAll();

  // Parse FEN into separate components
  std::istringstream ss(fen);
  std::string piecePlacement, activeColor, castling, enPassant;
  ss >> piecePlacement >> activeColor >> castling >> enPassant >>
      m_nHalfMoveClock >> m_nFullMoveNumber;

  // Parse piece placement
  // FEN notation goes from rank 8 to rank 1, files are in 1->8 order
  int rank = core::RANK_8;
  int file = core::FILE_A;
  for (char c : piecePlacement) {
    // '/' denotes next rank (-1)
    if (c == '/') {
      // Move to the lower rank and start from A file
      rank--;
      file = core::FILE_A;
      continue; // move to another piece placement char
    }

    // Digits (1-8) denote number of empty squares
    if (std::isdigit(c)) {
      // Skip empty it squares
      file += (c - '0'); // Neat and dirty way to convert ascii digit to int
      continue;          // move to another piece placement char
    }

    // Piece color. Upper case is used for white pieces
    core::Color color =
        std::isupper(c) ? core::Color::WHITE : core::Color::BLACK;
    // Fetch piece type from notation
    core::PieceType type = core::PieceType::fromChar(c);
    // Set up position
    core::Position pos = core::Position(rank, file);
    // Place piece
    m_board.placePiece(pos, type, color);

    // move to another file
    file++;
  }

  // Parse color to move
  m_sideToMove = (activeColor == "w") ? core::Color::WHITE : core::Color::BLACK;

  // Parse castling rights
  bool whiteKingside = castling.find('K') != std::string::npos;
  bool whiteQueenside = castling.find('Q') != std::string::npos;
  bool blackKingside = castling.find('k') != std::string::npos;
  bool blackQueenside = castling.find('q') != std::string::npos;

  m_castlingRights = CastlingRights(whiteKingside, whiteQueenside,
                                    blackKingside, blackQueenside);

  // Parse en passant target
  if (enPassant != "-") {
    // parse position rank and file
    int epFile = enPassant[0] - 'a'; // Convert file to 0-7 format
    int epRank = enPassant[1] - '1'; // Convert rank to 0-7 format
    m_enPassantTarget = core::Position(epRank, epFile);
  } else {
    m_enPassantTarget = std::nullopt;
  }

  updateOutcome();
}

/**
 * @brief Return mutable reference to the board adapter
 *
 * @return Board&
 */
Board &GameState::getBoard() { return m_board; }

/**
 * @brief Return immutable reference to the board adapter
 *
 * @return Board&
 */
const Board &GameState::getBoard() const { return m_board; }

/**
 * @brief Get mutable castling rights
 *
 * @return CastlingRights&
 */
CastlingRights &GameState::getCastlingRights() { return m_castlingRights; }

/**
 * @brief Get immutable castling rights
 *
 * @return CastlingRights&
 */
const CastlingRights &GameState::getCastlingRights() const {
  return m_castlingRights;
}

/**
 * @brief Get current move color
 *
 * @return core::Color
 */
core::Color GameState::getSideToMove() const { return m_sideToMove; }

/**
 * @brief Get en passant target square
 *
 * @return std::optional<core::Position> nullopt if en passant target position
 * is unset
 */
std::optional<core::Position> GameState::getEnPassantTarget() const {
  return m_enPassantTarget;
}

/**
 * @brief Return half move clock value
 *
 * @return int
 */
int GameState::getHalfMoveClock() const { return m_nHalfMoveClock; }

/**
 * @brief Return move number
 *
 * @return int
 */
int GameState::getFullMoveNumber() const { return m_nFullMoveNumber; }

/**
 * @brief Get game outcome (or if it is still in progress)
 *
 * @return GameOutcome
 */
GameOutcome GameState::getOutcome() const { return m_gameOutcome; }

/**
 * @brief Get move history
 *
 * @return const std::vector<Move>&
 */
const std::vector<Move> &GameState::getMoveHistory() const {
  return m_moveHistory;
}

/**
 * @brief Get legal moves for the whole board
 *
 * @return std::vector<Move>
 */
std::vector<Move> GameState::getLegalMoves() const {
  // Generate current move context
  MoveContext context = createMoveContext();
  // Generate pseudo legal moves
  std::vector<Move> pseudoLegalMoves = m_moveGenerator.generateMoves(context);
  // Return moves with illegal moves filtered out
  return m_moveValidator.filterLegalMoves(pseudoLegalMoves, context);
}

/**
 * @brief Get legal moves from a position
 *
 * @return std::vector<Move>
 */
std::vector<Move> GameState::getLegalMovesFrom(core::Position pos) const {
  // Generate current move context
  MoveContext context = createMoveContext();
  // Get piece at the position
  auto piece = m_board.getPieceAt(pos);
  if (!piece) {
    return {}; // No legal moves for no piece
  }
  // Generate pseudo legal moves
  std::vector<Move> pseudoLegalMoves =
      m_moveGenerator.generatePieceMoves(pos, *piece, context);
  // Return moves with illegal moves filtered out
  return m_moveValidator.filterLegalMoves(pseudoLegalMoves, context);
}

/**
 * @brief Validate and execute the move
 *
 * @param move Move to try and execute
 * @return true If move is successful
 * @return false If move is unsuccessful
 */
bool GameState::tryMove(const Move &move) {
  // Can't move unless game is in progress
  if (m_gameOutcome != GameOutcome::IN_PROGRESS) {
    return false;
  }

  // Check if piece exists and belongs to the player
  auto piece = m_board.getPieceAt(move.getFrom());
  if (!piece || piece->getColor() != m_sideToMove) {
    // Should not end up here but who knows what can happen
    return false;
  }

  // Reject promotion without a promotion piece
  if (move.isPromotion() && !move.getPromotionPiece().has_value()) {
    // UI layer must set promotion piece before trying the move
    // We could auto-promote to queen but sometimes you need a knight
    return false;
  }

  // Check if move is legal in case we somehow pass illegal move
  MoveContext context = createMoveContext();
  if (!m_moveValidator.isLegal(move, context)) {
    return false;
  }

  applyMove(move);
  return true;
}

/**
 * @brief Execute the move and update context flags
 *
 * @param move Move to execute
 */
void GameState::applyMove(const Move &move) {
  Logger::FunctionScope logScope;

  Logger::debug(moveDebug(), "Applying move: " + move.toAlgebraic());
  Logger::debug(moveDebug(), "From: " + move.getFrom().toString() +
                                 " To: " + move.getTo().toString() + " Type: " +
                                 std::to_string((int)move.getType()));

  // Move the piece on the board
  m_board.movePiece(move.getFrom(), move.getTo());
  m_moveHistory.push_back(move);

  // Handle pawn promotion
  if (move.isPromotion()) {
    Logger::debug(moveDebug(),
                  "Handling promotion to " +
                      std::string(1, move.getPromotionPiece()->getLetter()));

    // Remove pawn and replace it with a new piece
    m_board.removePiece(move.getTo());
    m_board.placePiece(move.getTo(), *move.getPromotionPiece(),
                       move.getColor());
  }

  // Handle castling
  if (move.isCastling()) {
    Logger::debug(moveDebug(), "Handling castling");

    // Detect which rook to move and where
    int rookStartingFile = move.getType() == MoveType::CASTLE_KINGSIDE
                               ? core::FILE_H
                               : core::FILE_A;
    int rookDestinationFile = move.getType() == MoveType::CASTLE_KINGSIDE
                                  ? core::FILE_F
                                  : core::FILE_D;
    // Set up rook positions
    int rank = move.getTo().getRank();
    core::Position rookStartingPos(rank, rookStartingFile);
    core::Position rookDestinationPos(rank, rookDestinationFile);
    // Move rook
    m_board.movePiece(rookStartingPos, rookDestinationPos);
  }

  // Handle en-passant capture
  if (move.isEnPassant()) {
    // Calculate where is the piece captured with en passant
    int direction = move.getColor() == core::Color::WHITE ? 1 : -1;
    core::Position destination = move.getTo();
    // Captured piece will be in the opposite rank of the movement direction so
    // using subtraction
    core::Position capturePiecePosition = core::Position(
        destination.getRank() - direction, destination.getFile());

    Logger::debug(moveDebug(), "Handling en passant, removing piece at " +
                                   capturePiecePosition.toString());

    // Remove captured piece
    m_board.removePiece(capturePiecePosition);
  }

  // Update context flags
  updateEnPassantTarget(move);
  updateCastlingRights(move);
  updateMoveCounter(move);
  switchTurn();

  // Update move's check/checkmate flags in the move history
  Move &lastMove = m_moveHistory.back();
  MoveContext postMoveContext = createMoveContext(); // Context for the opponent
  // Check if opponent is in check
  if (m_moveValidator.isInCheck(lastMove.getColor().opposite(),
                                postMoveContext)) {
    lastMove.setCheck();

    // Check if opponent has any legal moves
    std::vector<Move> opponentMoves =
        m_moveGenerator.generateMoves(postMoveContext);
    if (!m_moveValidator.hasLegalMoves(opponentMoves, postMoveContext)) {
      lastMove.setCheckmate();
    }
  }

  // Update game status
  updateOutcome();

  Logger::debug(moveDebug(), "Move applied");
}

/**
 * @brief Update Castling rights after a move
 *
 * @param move Move to base update upon
 */
void GameState::updateCastlingRights(const Move &move) {
  Logger::FunctionScope logScope;

  Logger::debug(
      castlingDebug(),
      "Updating castling rights for move: " + move.toAlgebraic() + " from " +
          move.getFrom().toString() + " to " + move.getTo().toString() +
          " type: " + std::to_string(static_cast<int>(move.getPieceType())));

  Logger::debug(
      castlingDebug(),
      "Current rights - White K:" +
          std::to_string(
              m_castlingRights.canCastleKingside(core::Color::WHITE)) +
          " Q:" +
          std::to_string(
              m_castlingRights.canCastleQueenside(core::Color::WHITE)) +
          " Black K:" +
          std::to_string(
              m_castlingRights.canCastleKingside(core::Color::BLACK)) +
          " Q:" +
          std::to_string(
              m_castlingRights.canCastleQueenside(core::Color::BLACK)));

  // Get color for the move
  core::Color color = move.getColor();

  // Check if king has moved
  if (move.getPieceType() == core::PieceType::KING) {
    Logger::debug(castlingDebug(), "King moved. Revoking all castling for " +
                                       move.getColor().toString());
    // Color no longer can castle on any side
    m_castlingRights.revokeAll(color);
  }

  // Check if A file (queenside) rook has moved
  if (move.getPieceType() == core::PieceType::ROOK &&
      move.getFrom().getFile() == core::FILE_A) {
    Logger::debug(castlingDebug(),
                  "Rook moved. Revoking queenside castling for " +
                      move.getColor().toString());
    m_castlingRights.revokeQueenside(color);
  }

  // Check if H file (kingside) rook has moved
  if (move.getPieceType() == core::PieceType::ROOK &&
      move.getFrom().getFile() == core::FILE_H) {
    Logger::debug(castlingDebug(),
                  "Rook moved. Revoking kingside castling for " +
                      move.getColor().toString());
    m_castlingRights.revokeKingside(color);
  }

  // Remove opponent's castling rights on the one of the sides
  int opponentRank = color == core::Color::WHITE ? core::RANK_8 : core::RANK_1;
  core::Color opponent = color.opposite();

  // Check if opponent's queen side rook origin position is overtaken
  if (move.getTo() == core::Position(opponentRank, core::FILE_A)) {
    Logger::debug(castlingDebug(),
                  "Rook captured. Revoking queenside castling for " +
                      opponent.toString());
    m_castlingRights.revokeQueenside(opponent);
  }

  // Check if opponent's king side rook origin position is overtaken
  if (move.getTo() == core::Position(opponentRank, core::FILE_H)) {
    Logger::debug(castlingDebug(),
                  "Rook captured. Revoking kingside castling for " +
                      opponent.toString());
    m_castlingRights.revokeKingside(opponent);
  }

  Logger::debug(
      castlingDebug(),
      "Updated rights - White K:" +
          std::to_string(
              m_castlingRights.canCastleKingside(core::Color::WHITE)) +
          " Q:" +
          std::to_string(
              m_castlingRights.canCastleQueenside(core::Color::WHITE)) +
          " Black K:" +
          std::to_string(
              m_castlingRights.canCastleKingside(core::Color::BLACK)) +
          " Q:" +
          std::to_string(
              m_castlingRights.canCastleQueenside(core::Color::BLACK)));
}

/**
 * @brief Update en passant target
 *
 * @note En Passant target is a square behind a pawn that double-pushed
 * @param move Move to base update upon
 */
void GameState::updateEnPassantTarget(const Move &move) {
  // Exit early if not a pawn move
  if (move.getPieceType() != core::PieceType::PAWN) {
    // En Passant is valid only right after double push and not later
    m_enPassantTarget = std::nullopt;
    return;
  }

  // Find pawn origin rank
  int originRank =
      move.getColor() == core::Color::WHITE ? core::RANK_2 : core::RANK_7;

  // Check if move started at the origin rank
  if (move.getFrom().getRank() != originRank) {
    // Reset En Passant target
    m_enPassantTarget = std::nullopt;
    return;
  }

  // Get color movement direction
  int direction = move.getColor() == core::Color::WHITE ? 1 : -1;
  // Check pawn moved 2 ranks
  if (move.getTo().getRank() != originRank + (2 * direction)) {
    // Reset En Passant target
    m_enPassantTarget = std::nullopt;
    return;
  }

  // Set en passant a square behind pawn that double-pushed
  m_enPassantTarget =
      core::Position(originRank + direction, move.getTo().getFile());
}

/**
 * @brief Switch turn color
 */
void GameState::switchTurn() { m_sideToMove = m_sideToMove.opposite(); }

/**
 * @brief Update half and full move counters
 *
 * @param move Move to base update upon
 */
void GameState::updateMoveCounter(const Move &move) {
  // Update half move clock to check for 50 move rule
  // See https://www.chess.com/terms/50-move-rule-chess#what
  if (move.isCapture() || move.getPieceType() == core::PieceType::PAWN) {
    // Reset half move clock on captures or pawn moves
    m_nHalfMoveClock = 0;
  } else {
    // Otherwise, increase it
    m_nHalfMoveClock++;
  }

  // Increase full move number after black has moved
  if (move.getColor() == core::Color::BLACK) {
    m_nFullMoveNumber++;
  }
}

/**
 * @brief Update game status/outcome
 *
 */
void GameState::updateOutcome() {
  // Game is in progress for initial position
  if (m_moveHistory.empty()) {
    m_gameOutcome = GameOutcome::IN_PROGRESS;
    return;
  }

  Move lastMove = m_moveHistory.back();

  // Check for checkmate
  if (lastMove.isCheckmate()) {
    m_gameOutcome = lastMove.getColor() == core::Color::WHITE
                        ? GameOutcome::CHECKMATE_WHITE_WINS
                        : GameOutcome::CHECKMATE_BLACK_WINS;
    return;
  }

  // Check for stalemate
  MoveContext context = createMoveContext();
  bool isChecked = m_moveValidator.isInCheck(m_sideToMove, context);
  std::vector<Move> pseudoLegalMoves = m_moveGenerator.generateMoves(context);
  bool hasLegalMoves = m_moveValidator.hasLegalMoves(pseudoLegalMoves, context);
  if (!isChecked && !hasLegalMoves) {
    m_gameOutcome = GameOutcome::STALEMATE;
    return;
  }

  // Check for 50 move rule (100 half-moves)
  if (getHalfMoveClock() >= core::MAX_HALFMOVE_CLOCK) {
    m_gameOutcome = GameOutcome::DRAW_FIFTY_MOVE;
    return;
  }

  // TODO: Add insufficient

  // Default
  m_gameOutcome = GameOutcome::IN_PROGRESS;
}

/**
 * @brief Generate a context snapshot of the game state for move generation and
 * validation
 *
 * @return MoveContext
 */
MoveContext GameState::createMoveContext() const {
  return MoveContext(m_castlingRights, m_enPassantTarget, m_sideToMove,
                     m_bitboards.getAllOccupancy());
}

} // namespace game