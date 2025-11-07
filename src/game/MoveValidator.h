/**
 * @file MoveValidator.h
 * @brief Validator for chess moves
 */
#pragma once

#include "bitboards/Manager.h"
#include "core/Color.h"
#include "core/Position.h"
#include "game/Move.h"
#include "game/MoveContext.h"
#include <vector>

namespace game {
/**
 * @brief Class for checking move validity
 *
 * MoveValidator evaluates current board state and
 * move context to validate a move
 */
class MoveValidator {
private:
  // BitBoards Manager reference for querying the bitboards
  bitboards::Manager &m_bitboards;

  // Helper method to find king's current position
  core::Position findKing(core::Color color);
  // Check if move results in leaving current color's king in check (i.e.
  // illegal move)
  bool leavesKingInCheck(const Move &move, const MoveContext &context);
  // Check if castling is legal. It is illegal to castle from/to check position
  bool isCastleLegal(const Move &move, const MoveContext &context);

public:
  // force direct initialization
  explicit MoveValidator(bitboards::Manager &bitboards)
      : m_bitboards(bitboards) {}

  // Remove illegal moves and return only legal moves
  std::vector<Move> filterLegalMoves(const std::vector<Move> &moves,
                                     const MoveContext &context);
  // Check if the move is legal
  bool isLegal(const Move &move, const MoveContext &context);
  // Check if a given color is currently in check
  bool isInCheck(core::Color color, const MoveContext &context);
  // Check if there are any legal moves (for stalemate)
  bool hasLegalMoves(const std::vector<Move> &moves,
                     const MoveContext &context);
  // Check if a given position is attacked by a color
  bool isSquareAttacked(const core::Position &pos, const MoveContext &context);
};
} // namespace game