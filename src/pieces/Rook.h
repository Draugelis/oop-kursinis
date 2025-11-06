#pragma once

#include "Piece.h"

namespace pieces {
class Rook : public Piece {
public:
  /**
   * @brief Construct a new Rook object
   *
   * @param color core::Color of the piece
   */
  Rook(core::Color color) : Piece(color, core::PieceType::ROOK) {}

  bitboards::BitBoard
  getMoveBitBoard(const core::Position &pos,
                  const game::MoveContext &context) const override;
};
} // namespace pieces