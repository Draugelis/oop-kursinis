#include "Move.h"
#include "core/Logging.h"

namespace game {

/**
 * @brief Construct a new Move object
 *
 * Defaults to NORMAL move type
 *
 * @param from Starting position
 * @param to Destination position
 * @param pieceType Piece type that moves
 */
Move::Move(core::Position from, core::Position to, core::PieceType pieceType,
           core::Color color)
    : m_from(from), m_to(to), m_pieceType(pieceType), m_type(MoveType::NORMAL),
      m_color(color), m_bIsCheck(false), m_bIsCheckmate(false),
      m_promotionPiece(std::nullopt) {}

/**
 * @brief Construct a new Move object
 *
 * Sets move type to a provided value
 *
 * @param from Starting position
 * @param to Destination position
 * @param pieceType Piece type that moves
 * @param type Move type
 */
Move::Move(core::Position from, core::Position to, core::PieceType pieceType,
           core::Color color, MoveType type)
    : m_from(from), m_to(to), m_pieceType(pieceType), m_type(type),
      m_color(color), m_bIsCheck(false), m_bIsCheckmate(false),
      m_promotionPiece(std::nullopt) {}

/**
 * @brief Construct a new Move object
 *
 * Pawn promotion move.
 * Move type should be PROMOTION or PROMOTION_CAPTURE
 *
 * @param from Starting position
 * @param to Destination position
 * @param pieceType Piece type that moves
 * @param type Move type
 * @param promotionPiece
 */
Move::Move(core::Position from, core::Position to, core::PieceType pieceType,
           core::Color color, MoveType type, core::PieceType promotionPiece)
    : m_from(from), m_to(to), m_pieceType(pieceType), m_type(type),
      m_color(color), m_bIsCheck(false), m_bIsCheckmate(false),
      m_promotionPiece(promotionPiece) {
  if ((type == MoveType::PROMOTION || type == MoveType::PROMOTION_CAPTURE) &&
      !m_promotionPiece.has_value()) {
    qCWarning(moveDebug)
        << "WARNING: Promotion move created without promotion piece!";
  }
}

/**
 * @brief Get starting position
 *
 * @return core::Position
 */
core::Position Move::getFrom() const { return m_from; }

/**
 * @brief Get destination position
 *
 * @return core::Position
 */
core::Position Move::getTo() const { return m_to; }

/**
 * @brief Get piece type that moves
 *
 * @return core::PieceType
 */
core::PieceType Move::getPieceType() const { return m_pieceType; }

/**
 * @brief Get color that moves
 *
 * @return core::PieceType
 */
core::Color Move::getColor() const { return m_color; }

/**
 * @brief Get move type
 *
 * @return MoveType
 */
MoveType Move::getType() const { return m_type; }

/**
 * @brief Get pawn promotion type
 *
 * @return std::optional<core::PieceType>
 */
std::optional<core::PieceType> Move::getPromotionPiece() const {
  return m_promotionPiece;
}

/**
 * @brief Check if move is capture type
 *
 * @return true If move is CAPTURE or PROMOTION_CAPTURE type
 * @return false If move is not CAPTURE or PROMOTION_CAPTURE type
 */
bool Move::isCapture() const {
  return m_type == MoveType::CAPTURE || m_type == MoveType::PROMOTION_CAPTURE;
}

/**
 * @brief Check if move is castling type
 *
 * @return true If move is CASTLE_KINGSIDE or CASTLE_QUEENSIDE type
 * @return false If move is not CASTLE_KINGSIDE or CASTLE_QUEENSIDE type
 */
bool Move::isCastling() const {
  return m_type == MoveType::CASTLE_KINGSIDE ||
         m_type == MoveType::CASTLE_QUEENSIDE;
}

/**
 * @brief Check if move is en passant type
 *
 * @return true If move is EN_PASSANT type
 * @return false If move is not EN_PASSANT type
 */
bool Move::isEnPassant() const { return m_type == MoveType::EN_PASSANT; }

/**
 * @brief Check if move is promotion type
 *
 * @return true If move is PROMOTION or PROMOTION_CAPTURE type
 * @return false If move is not PROMOTION or PROMOTION_CAPTURE type
 */
bool Move::isPromotion() const {
  return m_type == MoveType::PROMOTION || m_type == MoveType::PROMOTION_CAPTURE;
}

/**
 * @brief Check if move is check type
 *
 * @return true If move results in check
 * @return false If move doesn't result in check
 */
bool Move::isCheck() const { return m_bIsCheck; }

/**
 * @brief Check if move is checkmate type
 *
 * @return true If move results in checkmate
 * @return false If move doesn't result in checkmate
 */
bool Move::isCheckmate() const { return m_bIsCheckmate; }

/**
 * @brief Set move type
 *
 * @param type MoveType value
 */
void Move::setType(MoveType type) { m_type = type; }

/**
 * @brief Set capture move type
 *
 * @param isPromotion If move is a pawn promotion
 */
void Move::setCapture() { m_type = MoveType::CAPTURE; }

/**
 * @brief Set castling move type
 *
 * @param kingside If castling is done on the king side
 */
void Move::setCastling(bool kingside) {
  m_type = kingside ? MoveType::CASTLE_KINGSIDE : MoveType::CASTLE_QUEENSIDE;
}

/**
 * @brief Set en passant move type
 *
 */
void Move::setEnPassant() { m_type = MoveType::EN_PASSANT; }

/**
 * @brief Set promotion move type and piece
 *
 * @param promotionPiece To which piece pawn promotes
 * @param capture If move has piece capture
 */
void Move::setPromotion(core::PieceType promotionPiece, bool capture) {
  m_promotionPiece = promotionPiece;
  m_type = capture ? MoveType::PROMOTION_CAPTURE : MoveType::PROMOTION;
}

/**
 * @brief Set move as resulting in check
 *
 */
void Move::setCheck() { m_bIsCheck = true; }

/**
 * @brief Set move as resulting in checkmate
 *
 */
void Move::setCheckmate() { m_bIsCheckmate = true; }

/**
 * @brief Convert move to algebraic notation
 *
 * @see Algebraic notation info:
 * https://en.wikipedia.org/wiki/Algebraic_notation_(chess)
 * @return std::string Algebraic notation of the move
 */
std::string Move::toAlgebraic() const {
  // Early return for castling move types
  if (m_type == MoveType::CASTLE_KINGSIDE) {
    return "O-O";
  }

  if (m_type == MoveType::CASTLE_QUEENSIDE) {
    return "O-O-O";
  }

  // Construct algebraic notation
  std::string algebraic;

  // Pawn moves do not notate the piece letter
  // e.g. e4 (pawn to e4), Nc3 (knight to c3)
  if (m_pieceType != core::PieceType::PAWN) {
    algebraic += m_pieceType.getLetter();
  }

  // Setting up capture notation
  if (isCapture()) {
    // Pawn captures notate starting file. e.g. dxe6
    if (m_pieceType == core::PieceType::PAWN) {
      algebraic += static_cast<char>('a' + m_from.getFile());
    }
    algebraic += 'x'; // x denotes capture
  }

  algebraic += m_to.toString();

  // Setting up promotion notation. e.g. e8=Q (white promote to Queen)
  if (isPromotion()) {
    algebraic += '=';
    // NOTE: here we're being naive and unsafe by assuming that
    // promotion move type will surely have m_promotionPiece set.
    // I should add safe guards when I will have more time. But will I have it?
    algebraic += m_promotionPiece->getLetter();
  }

  // Setting up En Passant notation
  if (isEnPassant()) {
    algebraic += " e.p.";
  }

  // Setting up check and checkmate notations
  if (isCheckmate()) {
    algebraic += "#";
  } else if (isCheck()) {
    algebraic += '+';
  }

  return algebraic;
}

} // namespace game