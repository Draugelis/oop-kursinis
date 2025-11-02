/**
 * @file SlidingAttacks.h
 * @brief Utility for calculating sliding pieces attacks
 *
 */
#pragma once

#include "BitBoard.h"
#include "core/Position.h"

namespace bitboards {
/**
 * @brief Responsible for calculating available attack bitboards
 *
 */
class SlidingAttacks {
public:
  static BitBoard bishop(const core::Position &pos, const BitBoard &occupancy);
  static BitBoard rook(const core::Position &pos, const BitBoard &occupancy);
  static BitBoard queen(const core::Position &pos, const BitBoard &occupancy);
};
} // namespace bitboards
