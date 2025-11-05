/**
 * @file PieceType.h
 * @brief Enumeration class for chess piece types
 *
 */
#pragma once

#include <string>
#include <vector>

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

  // Get a string representation of the piece type
  const std::string toString() const;
  // Get a letter associated with a piece type
  const char getLetter() const;
  // Translate piece letter into a PieceType
  static PieceType fromChar(char c);
  // Return all Piece Types in enum
  static std::vector<PieceType> allTypes();

private:
  Value m_value;
};

} // namespace core