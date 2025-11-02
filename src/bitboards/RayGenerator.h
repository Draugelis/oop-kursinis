/**
 * @file RayGenerator.h
 * @brief Utility for ray casting during bitboard generation
 *
 */
#pragma once

#include "BitBoard.h"
#include "Direction.h"
#include "core/Position.h"

namespace bitboards {
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
