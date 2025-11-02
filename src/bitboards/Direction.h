/**
 * @file Direction.h
 * @brief Bitboard index offsets for directions
 */
#pragma once

namespace bitboards {
/**
 * @brief Enumeration for all 8 ray directions with their bitboard offsets
 *
 * @see Offset reference:
 * https://www.chessprogramming.org/General_Setwise_Operations#ShiftingBitboards
 */
enum class Direction : int {
  NORTH = 8,
  SOUTH = -8,
  EAST = 1,
  WEST = -1,
  NORTH_EAST = 9,  // NORTH + EAST
  NORTH_WEST = 7,  // NORTH + WEST
  SOUTH_EAST = -7, // SOUTH + EAST
  SOUTH_WEST = -9  // SOUTH + WEST
};

// Arithmetic operators to enable expressions like: 2*Direction::NORTH + Direction::EAST

/**
 * @brief Multiply direction by number
 */
constexpr int operator*(int num, Direction dir) {
  return num * static_cast<int>(dir);
}

/**
 * @brief Multiply direction by number
 */
constexpr int operator*(Direction dir, int num) {
  return num * static_cast<int>(dir);
}

/**
 * @brief Add two directions
 */
constexpr int operator+(Direction dir1, Direction dir2) {
  return static_cast<int>(dir1) + static_cast<int>(dir2);
}

/**
 * @brief Add number to direction
 */
constexpr int operator+(int num, Direction dir) {
  return num + static_cast<int>(dir);
}

/**
 * @brief Add number to direction
 */
constexpr int operator+(Direction dir, int num) {
  return static_cast<int>(dir) + num;
}
} // namespace bitboards