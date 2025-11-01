#include "Position.h"
#include "Constants.h"

/**
 * @brief Construct a Position from a bitboard index
 *
 * Converting linear bitboard index (0-63) to a board coordinates.
 * Index 0 represents a1 and index 63 represents h8
 *
 * @param index Bitboard index (0-63) where bits are numbered from LSB to MSB

 */
core::Position::Position(int index)
    : m_nRank(index / core::NUM_FILES), m_nFile(index % core::NUM_FILES) {}

int core::Position::getRank() const { return m_nRank; }

int core::Position::getFile() const { return m_nFile; }

/**
 * @brief Check whether position (rank and file) is within boundaries
 *
 * @return true If Position is within boundaries
 * @return false If Position is not within boundaries
 */
bool core::Position::isValid() const {
  return m_nRank >= core::MIN_RANK && m_nRank <= core::MAX_RANK &&
         m_nFile >= core::MIN_FILE && m_nFile <= core::MAX_FILE;
}

/**
 * @brief Convert Position to a bitboard index
 *
 * @return int Position index in a bitboard
 */
int core::Position::toIndex() const { return m_nRank * 8 + m_nFile; }

/**
 * @brief Convert position to a standard chess notation (e.g. "e4")
 *
 * Function offsets 'a' and '1' in ASCII table for file and rank
 * respectively
 *
 * @return std::string Standard chess notation
 */
std::string core::Position::toString() const {
  return {char('a' + m_nFile), char('1' + m_nRank)};
}

/**
 * @brief Compares two positions for equality
 *
 * Comparison checks whether both positions have
 * matching ranks and files
 *
 * @param other Other Position object
 * @return true If ranks and files match
 * @return false If ranks and files do not match
 */
bool core::Position::operator==(const core::Position &other) const {
  return m_nRank == other.m_nRank && m_nFile == other.m_nFile;
}

/**
 * @brief Compares two positions for inequality
 *
 * Opposite of operator==
 *
 * @param other Other Position object
 * @return true If ranks and files do not match
 * @return false If ranks and files match
 */
bool core::Position::operator!=(const core::Position &other) const {
  return !(*this == other);
}