#include "Position.h"
#include "Constants.h"

Core::Position::Position(int rank, int file) : m_nRank(rank), m_nFile(file) {}

/**
 * @brief Construct a Position from a bitboard index
 *
 * Converting linear bitboard index (0-63) to a board coordinates.
 * Index 0 represents a1 and index 63 represents h8
 *
 * @param index Bitboard index (0-63) where bits are numbered from LSB to MSB

 */
Core::Position::Position(int index)
    : m_nRank(index / Core::NUM_FILES), m_nFile(index % Core::NUM_FILES) {}

int Core::Position::getRank() const { return m_nRank; }

int Core::Position::getFile() const { return m_nFile; }

/**
 * @brief Check whether position (rank and file) is within boundaries
 *
 * @return true If Position is within boundaries
 * @return false If Position is not within boundaries
 */
bool Core::Position::isValid() const {
  return m_nRank >= Core::MIN_RANK && m_nRank <= Core::MAX_RANK &&
         m_nFile >= Core::MIN_FILE && m_nFile <= Core::MAX_FILE;
}

/**
 * @brief Convert Position to a bitboard index
 *
 * @return int Position index in a bitboard
 */
int Core::Position::toIndex() const { return m_nRank * 8 + m_nFile; }

/**
 * @brief Convert position to a standard chess notation (e.g. "e4")
 *
 * Function offsets 'a' and '1' in ASCII table for file and rank
 * respectively
 *
 * @return std::string Standard chess notation
 */
std::string Core::Position::toString() const {
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
bool Core::Position::operator==(const Core::Position &other) const {
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
bool Core::Position::operator!=(const Core::Position &other) const {
  return !(*this == other);
}