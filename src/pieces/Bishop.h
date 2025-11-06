#pragma once

#include "Piece.h"

namespace pieces {
class Bishop : public Piece {
public:
  /**
   * @brief Construct a new Bishop object
   *
   * @param color core::Color of the piece
   */
  Bishop(core::Color color) : Piece(color, core::PieceType::BISHOP) {}

  bitboards::BitBoard
  getMoveBitBoard(const core::Position &pos,
                  const game::MoveContext &context) const override;
};
} // namespace pieces