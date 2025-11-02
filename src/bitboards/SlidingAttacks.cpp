#include "SlidingAttacks.h"
#include "bitboards/RayGenerator.h"

/**
 * @brief Get bishop attack bitboard on diagonals
 *
 * @param pos Starting position
 * @param occupancy Bitboard of all pieces on the board
 * @return BitBoard of all squares along the ray (including blocking piece)
 */
bitboards::BitBoard
bitboards::SlidingAttacks::bishop(const core::Position &pos,
                                  const bitboards::BitBoard &occupancy) {
  return RayGenerator::castRay(pos, occupancy, Direction::NORTH_EAST) |
         RayGenerator::castRay(pos, occupancy, Direction::NORTH_WEST) |
         RayGenerator::castRay(pos, occupancy, Direction::SOUTH_EAST) |
         RayGenerator::castRay(pos, occupancy, Direction::SOUTH_WEST);
}

/**
 * @brief Get rook attack bitboard on axis
 *
 * @param pos Starting position
 * @param occupancy Bitboard of all pieces on the board
 * @return BitBoard of all squares along the ray (including blocking piece)
 */
bitboards::BitBoard
bitboards::SlidingAttacks::rook(const core::Position &pos,
                                const bitboards::BitBoard &occupancy) {
  return RayGenerator::castRay(pos, occupancy, Direction::NORTH) |
         RayGenerator::castRay(pos, occupancy, Direction::EAST) |
         RayGenerator::castRay(pos, occupancy, Direction::SOUTH) |
         RayGenerator::castRay(pos, occupancy, Direction::WEST);
}

/**
 * @brief Get queen attack bitboard by combining rook and bishop moves
 *
 * @param pos Starting position
 * @param occupancy Bitboard of all pieces on the board
 * @return BitBoard of all squares along the ray (including blocking piece)
 */
bitboards::BitBoard
bitboards::SlidingAttacks::queen(const core::Position &pos,
                                 const bitboards::BitBoard &occupancy) {
  return rook(pos, occupancy) | bishop(pos, occupancy);
}
