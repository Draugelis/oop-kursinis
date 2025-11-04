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
  bitboards::Manager &m_bitboards;

  // internal helpers
  core::Position findKing(core::Color color);
  bool leavesKingInCheck(const Move &move, const MoveContext &context);
  bool isCastleLegal(const Move &move, const MoveContext &context);
public:
  // force direct initialization
  explicit MoveValidator(bitboards::Manager &bitboards)
      : m_bitboards(bitboards) {}

  std::vector<Move> filterLegalMoves(const std::vector<Move> &moves,
                                     const MoveContext &context);
  bool isLegal(const Move &move, const MoveContext &context);
  bool isInCheck(core::Color color);
  bool hasLegalMoves(const MoveContext &context);
  bool isSquareAttacked(const core::Position &pos, core::Color byColor);
};
} // namespace game