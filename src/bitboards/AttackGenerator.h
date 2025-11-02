/**
 * @file AttackGenerator.h
 * @brief Facade for generating piece attacks
 */

#pragma once

#include "bitboards/AttackTables.h"
#include "bitboards/BitBoard.h"
#include "bitboards/SlidingAttacks.h"
#include "core/Color.h"
#include "core/PieceType.h"
#include "core/Position.h"

namespace bitboards {
/**
 * @brief Unified interface for attack generation
 *
 * AttackGenerator provides a single method to generate attacks
 * for any piece type, handling both jumping pieces and sliding pieces.
 */
class AttackGenerator {
public:
  /**
   * @brief Generate attack bitboard for any piece
   *
   * @param type Piece type
   * @param pos Square position of the piece
   * @param color Piece color
   * @param occupancy Bitboard of all pieces on the board
   * @return BitBoard All squares the piece attacks
   */
  static BitBoard getAttacks(core::PieceType type, core::Position pos,
                             core::Color color, const BitBoard &occupancy) {
    switch (type) {
    case core::PieceType::PAWN:
      return AttackTables::getPawnAttacks(pos, color);
    case core::PieceType::KNIGHT:
      return AttackTables::getKnightAttacks(pos);
    case core::PieceType::BISHOP:
      return SlidingAttacks::bishop(pos, occupancy);
    case core::PieceType::ROOK:
      return SlidingAttacks::rook(pos, occupancy);
    case core::PieceType::QUEEN:
      return SlidingAttacks::queen(pos, occupancy);
    case core::PieceType::KING:
      return AttackTables::getKingAttacks(pos);
    }
    return 0ULL;
  }
};
} // namespace bitboards