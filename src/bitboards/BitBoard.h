/**
 * @file BitBoard.h
 * @brief Bitboard class implementation
 *
 */
#pragma once

#include "core/Position.h"
#include <cstdint> // for uint64_t
#include <vector>

namespace bitboards {
/**
 * @brief BitBoard representation class
 *
 * BitBoard is 64-bit unsigned int where each
 * bit represents a taken or available position
 * on a chess board.
 *
 * @note Each piece type and color combination has its own bitboard
 * @see https://www.chessprogramming.org/Bitboards
 */
class BitBoard {
private:
  uint64_t m_ullBits;

public:
  // Good ol' constructors
  BitBoard() : m_ullBits(0) {}
  BitBoard(uint64_t value) : m_ullBits(value) {}
  // Getters
  bool isSet(const core::Position &pos) const;
  bool isSet(int index) const;
  uint64_t getBits() const;
  core::Position getFirstSetBit() const;
  std::vector<core::Position> getSetBitPositions() const;
  // Setters
  void setBit(const core::Position &pos);
  void setBit(int index);
  void clearBit(const core::Position &pos);
  // Bitwise operator overloads
  BitBoard operator|(const BitBoard &other) const; // OR
  BitBoard operator&(const BitBoard &other) const; // AND
  BitBoard operator&=(const BitBoard &other);      // AND assignment
  BitBoard operator|=(const BitBoard &other);      // Compound assignment
  BitBoard operator^(const BitBoard &other) const; // XOR
  BitBoard operator^=(const BitBoard &other);      // XOR assignment
  BitBoard operator~() const;                      // NOT
  BitBoard operator<<(int shift) const;            // Shift left
  BitBoard operator>>(int shift) const;            // Shift right
};
} // namespace bitboards
