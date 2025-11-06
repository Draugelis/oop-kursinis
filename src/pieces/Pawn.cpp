#include "Pawn.h"
#include "bitboards/AttackGenerator.h"
#include "game/MoveContext.h"

namespace pieces {
/**
 * @brief Generate all pseudo-legal moves
 *
 * Returns single and double pushes and attacks.
 *
 * @param pos Current position
 * @param context Current move context
 * @return bitboards::BitBoard Bitboard with all moves
 */
bitboards::BitBoard
Pawn::getMoveBitBoard(const core::Position &pos,
                      const game::MoveContext &context) const {
  // Get base attack table
  bitboards::BitBoard moves = bitboards::AttackGenerator::getAttacks(
      m_type, pos, m_color, context.getOccupancy());

  // Get current rank and file
  int rank = pos.getRank();
  int file = pos.getFile();

  // Single push (normal pawn move)
  moves.setBit(core::Position(rank + 1, file));

  // Double push (only from starting position)
  if (!m_bHasMoved) {
    moves.setBit(core::Position(rank + 2, file));
  }

  return moves;
}
} // namespace pieces