#include "Knight.h"
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
Knight::getMoveBitBoard(const core::Position &pos,
                        const game::MoveContext &context) const {
  // Pass-through the attacks since there are no special moves
  return bitboards::AttackGenerator::getAttacks(m_type, pos, m_color,
                                                context.getOccupancy());
}
} // namespace pieces