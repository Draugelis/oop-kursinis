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

  // Remove attacks on empty tiles
  moves &= context.getOccupancy();

  // Get current rank and file
  int rank = pos.getRank();
  int file = pos.getFile();

  // Move direction
  int moveDirection = (m_color == core::Color::WHITE) ? 1 : -1;

  // Single push (normal pawn move)
  // Can move if path is not blocked
  core::Position oneAhead(rank + moveDirection, file);
  bool pathAvailable = !context.getOccupancy().isSet(oneAhead);
  if (pathAvailable) {
    moves.setBit(oneAhead);
  }

  // Is pawn still on starting rank
  bool isStartingRank =
      ((m_color == core::Color::WHITE && rank == core::RANK_2) ||
       (m_color == core::Color::BLACK && rank == core::RANK_7));

  // Double push
  // Only from starting rank and if path is not blocked on both tiles
  core::Position twoAhead(rank + 2 * moveDirection, file);
  pathAvailable = pathAvailable && !context.getOccupancy().isSet(twoAhead);
  if (isStartingRank && pathAvailable) {
    moves.setBit(twoAhead);
  }

  return moves;
}
} // namespace pieces