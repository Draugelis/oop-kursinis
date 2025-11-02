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
 * @brief Stateless utility class in all directions
 *
 * RayGenerator provides methods for casting rays along 8 cardinal directions.
 * This class is stateless and does not require instantiation
 */
class RayGenerator {
public:
  RayGenerator() = delete; // Prevent instantiation

  static BitBoard north(core::Position pos, const BitBoard &occupancy);
  static BitBoard south(core::Position pos, const BitBoard &occupancy);
  static BitBoard east(core::Position pos, const BitBoard &occupancy);
  static BitBoard west(core::Position pos, const BitBoard &occupancy);
  static BitBoard northEast(core::Position pos, const BitBoard &occupancy);
  static BitBoard northWest(core::Position pos, const BitBoard &occupancy);
  static BitBoard southEast(core::Position pos, const BitBoard &occupancy);
  static BitBoard southWest(core::Position pos, const BitBoard &occupancy);
};
} // namespace bitboards