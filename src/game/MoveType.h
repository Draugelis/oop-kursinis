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
    NORMAL,
    CAPTURE,
    CASTLE_KINGSIDE,
    CASTLE_QUEENSIDE,
    EN_PASSANT,
    PROMOTION,
    PROMOTION_CAPTURE
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
