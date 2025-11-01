#pragma once

#include "Piece.h"

namespace pieces {
class Queen : public Piece {
public:
  /**
   * @brief Construct a new Queen object
   *
   * @param color core::Color of the piece
   */
  Queen(core::Color color) : Piece(color, core::PieceType::QUEEN) {}

  bitboards::BitBoard
  getMoveBitBoard(const core::Position &pos,
                  const board::BoardState &board) const override;
};
} // namespace pieces