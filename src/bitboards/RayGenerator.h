/**
 * @file RayGenerator.h
 * @brief Utility for ray casting during bitboard generation
 *
 */
#pragma once

#include "BitBoard.h"
#include "core/Position.h"

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

/**
 * @brief Stateless utility class in all directions
 *
 * RayGenerator provides methods for casting rays along the 8 cardinal
 * and diagonal directions from a given position until blocked by occupancy.
 * All methods are static and require no instantiation.
 */
class RayGenerator {
private:
  static int getMaxSteps(core::Position pos, Direction dir);

public:
  RayGenerator() = delete; // Prevent instantiation

  static BitBoard castRay(core::Position pos, const BitBoard &occupancy,
                          Direction dir);
};
} // namespace bitboards