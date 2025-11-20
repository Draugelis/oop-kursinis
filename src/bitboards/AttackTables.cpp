#include "AttackTables.h"
#include "Direction.h"
#include "core/Constants.h"

namespace bitboards {
// Define static members
std::array<BitBoard, core::TOTAL_SQUARES> AttackTables::s_arrKnightAttacks;
std::array<BitBoard, core::TOTAL_SQUARES> AttackTables::s_arrKingAttacks;
std::array<BitBoard, core::TOTAL_SQUARES> AttackTables::s_arrPawnAttacksWhite;
std::array<BitBoard, core::TOTAL_SQUARES> AttackTables::s_arrPawnAttacksBlack;
bool AttackTables::s_bInitialized = false;

/**
 * @brief Generates Knight attack bitboards for all 64 squares
 *
 * Knight moves in a L share (2+1 squares in any direction)
 */
void AttackTables::generateKnightAttacks() {
  const int knightIndexOffsets[8] = {
      2 * Direction::NORTH + Direction::EAST,
      2 * Direction::NORTH + Direction::WEST,
      2 * Direction::WEST + Direction::NORTH,
      2 * Direction::WEST + Direction::SOUTH,
      2 * Direction::EAST + Direction::NORTH,
      2 * Direction::EAST + Direction::SOUTH,
      2 * Direction::SOUTH + Direction::EAST,
      2 * Direction::SOUTH + Direction::WEST,
  };

  for (int index = 0; index < core::TOTAL_SQUARES; index++) {
    BitBoard attacks;
    // Starting position
    const int fromRank = index / core::NUM_RANKS;
    const int fromFile = index % core::NUM_RANKS;

    for (int offset : knightIndexOffsets) {
      const int targetIndex = index + offset;

      // Check whether target index is within the board
      if (targetIndex < 0 || targetIndex >= 64) {
        continue;
      }

      // Check whether knight wraps around the board after the move
      // New indices may point to squares on the other side of the board
      const int toRank = targetIndex / core::NUM_RANKS;
      const int toFile = targetIndex % core::NUM_RANKS;
      // Knight shall only move 2 squares in one direction and 1 in the other
      const int rankDiff = std::abs(toRank - fromRank);
      const int fileDiff = std::abs(toFile - fromFile);

      // Valid diffs (2,1) or (1,2)
      if ((rankDiff == 2 && fileDiff == 1) ||
          (rankDiff == 1 && fileDiff == 2)) {
        attacks.setBit(targetIndex);
      }
    }
    s_arrKnightAttacks[index] = attacks;
  }
}

/**
 * @brief Generates King attack bitboards for all 64 squares
 *
 * King moves to all directions 1 square away
 */
void AttackTables::generateKingAttacks() {
  constexpr Direction kingDirections[8] = {
      Direction::NORTH,      Direction::SOUTH,      Direction::EAST,
      Direction::WEST,       Direction::NORTH_EAST, Direction::NORTH_WEST,
      Direction::SOUTH_EAST, Direction::SOUTH_WEST,
  };

  for (int index = 0; index < core::TOTAL_SQUARES; index++) {
    BitBoard attacks;
    // Starting position
    const int fromRank = index / core::NUM_RANKS;
    const int fromFile = index % core::NUM_RANKS;

    for (Direction dir : kingDirections) {
      int offset = static_cast<int>(dir);
      const int targetIndex = index + offset;

      // Check whether target index is within the board
      if (targetIndex < 0 || targetIndex >= 64) {
        continue;
      }

      // Check whether king wraps around the board after the move
      // New indices may point to squares on the other side of the board
      const int toRank = targetIndex / core::NUM_RANKS;
      const int toFile = targetIndex % core::NUM_RANKS;
      // King shall move only 1 square away
      const int rankDiff = std::abs(toRank - fromRank);
      const int fileDiff = std::abs(toFile - fromFile);

      // Valid diffs (0,1), (1,0), (1,1)
      if ((rankDiff == 0 && fileDiff == 1) ||
          (rankDiff == 1 && fileDiff == 0) ||
          (rankDiff == 1 && fileDiff == 1)) {
        attacks.setBit(targetIndex);
      }
    }
    s_arrKingAttacks[index] = attacks;
  }
}

/**
 * @brief Generates Pawn attack bitboards for all 64 squares
 *
 * Separate bitboards are used for each color since pawns move only one
 * direction (White->North, Black->South). These bitboards do not include
 * special case for en passant.
 *
 */
void AttackTables::generatePawnAttacks() {
  for (int index = 0; index < core::TOTAL_SQUARES; index++) {
    BitBoard whiteAttacks;
    BitBoard blackAttacks;
    // Starting position
    const int fromRank = index / core::NUM_RANKS;
    const int fromFile = index % core::NUM_RANKS;

    if (fromRank == core::RANK_1 || fromRank == core::RANK_8) {
      // Pawns can't attack or be in ranks 1 or 8 so filling with blank these
      // indices with empty bitboards
      s_arrPawnAttacksWhite[index] = whiteAttacks;
      s_arrPawnAttacksBlack[index] = blackAttacks;
      continue;
    }

    // Can attack the west side
    if (fromFile > core::FILE_A) {
      whiteAttacks.setBit(index + Direction::NORTH_WEST);
      blackAttacks.setBit(index + Direction::SOUTH_WEST);
    }

    // Can attack the east side
    if (fromFile < core::FILE_H) {
      whiteAttacks.setBit(index + Direction::NORTH_EAST);
      blackAttacks.setBit(index + Direction::SOUTH_EAST);
    }

    s_arrPawnAttacksWhite[index] = whiteAttacks;
    s_arrPawnAttacksBlack[index] = blackAttacks;
  }
}

void AttackTables::initialize() {
  generateKnightAttacks();
  generateKingAttacks();
  generatePawnAttacks();
  s_bInitialized = true;
}

/**
 * @brief Get attack bitboard for piece at position
 *
 * @param pos Current position
 * @return BitBoard
 */
BitBoard
AttackTables::getKnightAttacks(const core::Position &pos) {
  return s_arrKnightAttacks[pos.toIndex()];
}

/**
 * @brief Get attack bitboard for piece at position
 *
 * @param pos Current position
 * @return BitBoard
 */
BitBoard
AttackTables::getKingAttacks(const core::Position &pos) {
  return s_arrKingAttacks[pos.toIndex()];
}

/**
 * @brief Get attack bitboard for piece at position
 *
 * @param pos Current position
 * @param color Pawn's color
 * @return BitBoard
 */
BitBoard
AttackTables::getPawnAttacks(const core::Position &pos,
                                        core::Color color) {
  return (color == core::Color::WHITE) ? s_arrPawnAttacksWhite[pos.toIndex()]
                                       : s_arrPawnAttacksBlack[pos.toIndex()];
}
} // namespace bitboards
