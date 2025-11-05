/**
 * @file MoveType.h
 * @brief Enumeration class for move types
 */
#pragma once

namespace game {
/**
 * @brief Enumerator class for move types
 *
 * Move types can vary from normal movement
 * to capture or special actions
 */
class MoveType {
public:
  enum Value {
    NORMAL,           // Normal move without captures or special conditions
    CAPTURE,          // Normal capture move
    CASTLE_KINGSIDE,  // Castling on the king side (O-O)
    CASTLE_QUEENSIDE, // Castling on the queen side (O-O-O)
    EN_PASSANT,       // Pawn en passant move
    PROMOTION,        // Pawn promotion
    PROMOTION_CAPTURE // Pawn capturing a piece and promoting
  };
  MoveType() = default;
  constexpr MoveType(Value value) : m_value(value) {}

  // Allow switch statements and comparisons
  constexpr operator Value() const { return m_value; }
  // prevent usage: if(moveType)
  explicit operator bool() = delete;

private:
  Value m_value;
};
} // namespace game
