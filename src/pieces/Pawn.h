#pragma once

#include "Piece.h"

namespace pieces {
class Pawn : public Piece {
public:
  /**
   * @brief Construct a new Pawn object
   *
   * @param color core::Color of the piece
   */
  Pawn(core::Color color) : Piece(color, core::PieceType::PAWN) {}

  bitboards::BitBoard
  getMoveBitBoard(const core::Position &pos,
                  const board::BoardState &board) const override;
};
} // namespace pieces