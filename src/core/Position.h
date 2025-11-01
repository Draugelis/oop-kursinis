/**
 * @file Position.h
 * @brief Position class for chess piece placement
 *
 */
#pragma once

#include <string>

namespace core {
/**
 * @brief Position class for representing chess piece placement
 *
 *
 * @see TODO: add reference to bitboards regardeing from index constructor
 */
class Position {
private:
  int m_nRank; // vertical axis (1-8)
  int m_nFile; // horizontal axis (a-h)

public:
  // Constructors
  Position(int rank, int file);
  Position(int index); // from bitboard index
  // Getters
  int getRank() const;
  int getFile() const;
  // Validator
  bool isValid() const;
  // Converters
  int toIndex() const;
  std::string toString() const;
  // Comparison operator overloads
  bool operator==(const Position &other) const;
  bool operator!=(const Position &other) const;
};

} // namespace core
