/**
 * @file AttackTables.h
 * @brief Attack tables for jumping pieces
 *
 */
#pragma once

#include "bitboards/BitBoard.h"
#include "core/Color.h"
#include "core/Constants.h"
#include "core/Position.h"
#include <array>

namespace bitboards {
/**
 * @brief Attack tables manager for jumping pieces
 *
 * Jumping pieces are King, Knight, and Pawn. Their moves
 * cannot be blocked by other pieces like for sliding pieces.
 *
 * @note: Pawn attacks assume that there are always pieces to capture
 */
class AttackTables {
private:
  // Pre-computed attack tables for jumping pieces
  static std::array<BitBoard, core::TOTAL_SQUARES> s_arrKnightAttacks;
  static std::array<BitBoard, core::TOTAL_SQUARES> s_arrKingAttacks;
  static std::array<BitBoard, core::TOTAL_SQUARES> s_arrPawnAttacksWhite;
  static std::array<BitBoard, core::TOTAL_SQUARES> s_arrPawnAttacksBlack;

  static bool s_bInitialized;
  static void generateKnightAttacks();
  static void generateKingAttacks();
  static void generatePawnAttacks();

public:
  static void initialize();

  // Get precomputed attack patterns
  static BitBoard getKnightAttacks(const core::Position &pos);
  static BitBoard getKingAttacks(const core::Position &pos);
  static BitBoard getPawnAttacks(const core::Position &pos, core::Color color);
};
} // namespace bitboards