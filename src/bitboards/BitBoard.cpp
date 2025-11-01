#include "BitBoard.h"
#include "core/Constants.h"
#include <stdexcept> // for runtime_error

/**
 * @brief Checks whether a bit in a position is set
 *
 * @param pos core::Position object
 * @return true If bit in a position is set (1)
 * @return false If bit in a position is not set (0)
 */
bool bitboards::BitBoard::isSet(const core::Position &pos) const {
  return m_ullBits & (1ULL << pos.toIndex());
}

/**
 * @brief Checks whether a bit with index is set
 *
 * @param index int corresponding to the positition index
 * @return true If bit at index is set (1)
 * @return false If bit at index is not set (0)
 */
bool bitboards::BitBoard::isSet(int index) const {
  return m_ullBits & (1ULL << index);
}

/**
 * @brief Returns unsigned long int for a bitboard
 *
 * @return uint64_t BitBoard representation
 */
uint64_t bitboards::BitBoard::getBits() const { return m_ullBits; }

/**
 * @brief Finds a position of the first set bit in the bitboard
 *
 * First set bit is found by calculating trailing zeroes in a bitboard
 *
 * @return core::Position of a first set bit
 */
core::Position bitboards::BitBoard::getFirstSetBit() const {
  if (m_ullBits == 0) {
    throw std::runtime_error("no bits are set in the bitboard");
  }

  /** TODO: add MSVC support */
  int index = __builtin_ctzll(m_ullBits); // Count trailing zeros

  return core::Position(index);
}

/**
 * @brief Finds all set positions in a bitboard
 *
 * @return std::vector<core::Position> Vector with all set positions
 */
std::vector<core::Position> bitboards::BitBoard::getSetBitPositions() const {
  std::vector<core::Position> result;

  // check all indices
  for (int i = 0; i < core::TOTAL_SQUARES; i++) {
    if (isSet(i)) {
      result.push_back(core::Position(i));
    }
  }

  return result;
}

/**
 * @brief Sets a bit to 1 in a given position
 *
 * Uses OR operation with mask where 1 is set at the target position index,
 * other bits are set to 0 to leave values unchanged
 *
 * @param pos core::Position
 */
void bitboards::BitBoard::setBit(const core::Position &pos) {
  m_ullBits |= (1ULL << pos.toIndex());
}

/**
 * @brief Sets a bit to 0 in a given position
 *
 * Uses AND operation with mask where 0 is set at the target position index,
 * other bits are set to 1 to leave values unchanged
 *
 * @param pos core::Position
 */
void bitboards::BitBoard::clearBit(const core::Position &pos) {
  m_ullBits &= ~(1ULL << pos.toIndex());
}

/**
 * @brief OR bitwise operation for BitBoard
 *
 *
 * Bitwise operation is done with m_ullBits members of both bitboards
 *
 * @param other second BitBoard operand
 * @return bitboards::BitBoard
 */
bitboards::BitBoard
bitboards::BitBoard::operator|(const bitboards::BitBoard &other) const {
  return BitBoard(m_ullBits | other.m_ullBits);
}

/**
 * @brief AND bitwise operation for BitBoard
 *
 *
 * Bitwise operation is done with m_ullBits members of both bitboards
 *
 * @param other second BitBoard operand
 * @return bitboards::BitBoard
 */
bitboards::BitBoard
bitboards::BitBoard::operator&(const bitboards::BitBoard &other) const {
  return BitBoard(m_ullBits & other.m_ullBits);
}

/**
 * @brief NOT bitwise operation for BitBoard
 *
 * Bitwise operation is done with m_ullBits member
 *
 * @return bitboards::BitBoard
 */
bitboards::BitBoard bitboards::BitBoard::operator~() const {
  return BitBoard(~m_ullBits);
}

/**
 * @brief Shift-left bitwise operation for BitBoard
 *
 * Bitwise operation is done with m_ullBits member
 *
 * @return bitboards::BitBoard
 */
bitboards::BitBoard bitboards::BitBoard::operator<<(int shift) const {
  return BitBoard(m_ullBits << shift);
}

/**
 * @brief Shift-right bitwise operation for BitBoard
 *
 * Bitwise operation is done with m_ullBits member
 *
 * @return bitboards::BitBoard
 */
bitboards::BitBoard bitboards::BitBoard::operator>>(int shift) const {
  return BitBoard(m_ullBits >> shift);
}

/**
 * @brief Compound assignment operation for BitBoard
 *
 * @param other second BitBoard operand
 * @return bitboards::BitBoard
 */
bitboards::BitBoard
bitboards::BitBoard::operator|=(const bitboards::BitBoard &other) {
  m_ullBits |= other.m_ullBits;
  return *this;
}