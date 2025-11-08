/**
 * @file MoveGenerator.h
 * @brief Pseudo-legal move generator
 */
#pragma once

#include "Move.h"
#include "bitboards/Manager.h"
#include "core/Position.h"
#include "game/MoveContext.h"
#include "pieces/Piece.h"
#include <vector>

namespace game {
/**
 * @brief Generates all possible pseudo-legal moves
 *
 * Uses piece's getMoveBitBoard() methods to orchestrate move generation
 * then converts given bitboard to a Move object vector
 *
 * @see MoveValidator is responsible for filtering legal moves
 */
class MoveGenerator {
private:
  // BitBoards Manager reference for querying the bitboards
  bitboards::Manager &m_bitboards;

public:
  // force direct initialization
  explicit MoveGenerator(bitboards::Manager &bitboards)
      : m_bitboards(bitboards) {}

  std::vector<Move> generateMoves(const MoveContext &context) const;
  std::vector<Move> generatePieceMoves(core::Position pos,
                                       const pieces::Piece &piece,
                                       const MoveContext &context) const;
};
} // namespace game
