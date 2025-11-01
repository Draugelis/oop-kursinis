#pragma once

#include "Piece.h"

namespace pieces {
class King : public Piece {
public:
  /**
   * @brief Construct a new King object
   *
   * @param color core::Color of the piece
   */
  King(core::Color color) : Piece(color, core::PieceType::KING) {}

  bitboards::BitBoard
  getMoveBitBoard(const core::Position &pos,
                  const board::BoardState &board) const override;
};
} // namespace pieces