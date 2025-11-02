#include "RayGenerator.h"

/**
 * @brief Cast a ray in a specified direction until blocked
 *
 * @param pos Starting position
 * @param occupancy Bitboard of all pieces on the board
 * @param dir Direction to cast the ray
 * @return BitBoard of all squares along the ray (including blocking piece)
 */
bitboards::BitBoard bitboards::RayGenerator::castRay(
    core::Position pos, const bitboards::BitBoard &occupancy, Direction dir) {
  bitboards::BitBoard attacks;
  int index = pos.toIndex();
  const int offset = static_cast<int>(dir); // Get offset from direction enum
  const int maxSteps = getMaxSteps(pos, dir);

  for (int step = 0; step < maxSteps; ++step) {
    index += offset;
    attacks.setBit(index);

    if (occupancy.isSet(index)) {
      break; // blocked
    }
  }

  return attacks;
}

/**
 * @brief Calculate maximum number of steps for ray casting
 *
 * @param pos Current position
 * @param dir Movement direction
 * @return int Number of maximum steps
 */
int bitboards::RayGenerator::getMaxSteps(core::Position pos, Direction dir) {
  const int rank = pos.getRank();
  const int file = pos.getFile();

  switch (dir) {
  case Direction::NORTH:
    return 7 - rank;
  case Direction::SOUTH:
    return rank;
  case Direction::EAST:
    return 7 - file;
  case Direction::WEST:
    return file;
  case Direction::NORTH_EAST:
    return std::min(7 - rank, 7 - file);
  case Direction::NORTH_WEST:
    return std::min(7 - rank, file);
  case Direction::SOUTH_EAST:
    return std::min(rank, 7 - file);
  case Direction::SOUTH_WEST:
    return std::min(rank, file);
  }
  return 0;
}
