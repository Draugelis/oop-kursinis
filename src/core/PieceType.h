/**
 * @file PieceType.h
 * @brief Enumeration class for chess piece types
 *
 */
#pragma once

#include <string>

namespace core {
/**
 * @brief Enumerator class for Chess piece types
 *
 * Color class implements enum for chess piece types
 * and contains supporting methods to fetch types string
 * name or letter
 *
 * @note Refered to https://stackoverflow.com/a/53284026 for implementation
 */
class PieceType {
public:
  enum Value {
    PAWN = 0,
    KNIGHT = 1,
    BISHOP = 2,
    ROOK = 3,
    QUEEN = 4,
    KING = 5
  };

  PieceType() = default;
  constexpr PieceType(Value value) : m_value(value) {}

  // Allows switch statements and comparisons
  constexpr operator Value() const { return m_value; }
  // prevent usage: if(pieceType)
  explicit operator bool() = delete;

  const std::string toString() const;
  char getLetter() const;
  static PieceType fromChar(char c);

private:
  Value m_value;
};

} // namespace core