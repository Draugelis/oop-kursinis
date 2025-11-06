#pragma once

#include "Piece.h"

namespace pieces {
class Knight : public Piece {
public:
  /**
   * @brief Construct a new Knight object
   *
   * @param color core::Color of the piece
   */
  Knight(core::Color color) : Piece(color, core::PieceType::KNIGHT) {}

  bitboards::BitBoard
  getMoveBitBoard(const core::Position &pos,
                  const game::MoveContext &context) const override;
};
} // namespace pieces