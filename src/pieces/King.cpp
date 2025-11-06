#include "King.h"
#include "bitboards/AttackGenerator.h"
#include "game/MoveContext.h"

namespace pieces {
/**
 * @brief Generate all pseudo-legal moves
 *
 * Include all attack positions and castling
 *
 * @param pos Current position
 * @param context Current move context
 * @return bitboards::BitBoard Bitboard with all moves
 */
bitboards::BitBoard
King::getMoveBitBoard(const core::Position &pos,
                      const game::MoveContext &context) const {
  // Get base attack table
  bitboards::BitBoard moves = bitboards::AttackGenerator::getAttacks(
      m_type, pos, m_color, context.getOccupancy());

  // Get current rank
  int rank = pos.getRank();
  // Add castling on the king side
  if (context.getCastlingRights().canCastleKingside(m_color)) {
    // Castling on king side -> move king to G file
    moves.setBit(core::Position(rank, core::FILE_G));
  }

  // Add castling on the queen side
  if (context.getCastlingRights().canCastleQueenside(m_color)) {
    // Castling on queen side -> move king to c file
    moves.setBit(core::Position(rank, core::FILE_C));
  }

  return moves;
}
} // namespace pieces