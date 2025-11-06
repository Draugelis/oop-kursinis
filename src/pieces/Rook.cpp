#include "Rook.h"
#include "bitboards/AttackGenerator.h"
#include "game/MoveContext.h"

namespace pieces {
/**
 * @brief Generate all pseudo-legal moves
 *
 * @param pos Current position
 * @param context Current move context
 * @return bitboards::BitBoard Bitboard with all moves
 */
bitboards::BitBoard
Rook::getMoveBitBoard(const core::Position &pos,
                      const game::MoveContext &context) const {
  // Pass-through the attacks since there are no special moves
  // Not including castling since that is a king mechanic rather than the rook
  return bitboards::AttackGenerator::getAttacks(m_type, pos, m_color,
                                                context.getOccupancy());
}
} // namespace pieces