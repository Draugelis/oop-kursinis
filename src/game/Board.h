/**
 * @file Board.h
 * @brief Board class implementation
 */
#pragma once

#include "bitboards/Manager.h"
#include "core/Color.h"
#include "core/PieceType.h"
#include "core/Position.h"
#include "pieces/Piece.h"
#include <memory>

namespace game {
/**
 * @brief Adapter for providing piece interface over BitBoardManager
 *
 * Board translates between bitboard representation and Piece objects (mostly
 * for UI)
 */
class Board {
private:
  bitboards::Manager &m_bitboards;

public:
  // force direct initialization
  explicit Board(bitboards::Manager &bitboards) : m_bitboards(bitboards) {}

  // Board query methods
  std::unique_ptr<pieces::Piece> getPieceAt(core::Position pos) const;
  bool isEmpty(core::Position pos) const;
  bool isOccupiedBy(core::Position pos, core::Color color) const;
  // Board manipulation methods
  void placePiece(core::Position pos, core::PieceType type, core::Color color);
  void removePiece(core::Position pos);
  void movePiece(core::Position from, core::Position to);
};
} // namespace game