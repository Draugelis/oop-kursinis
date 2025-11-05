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
  // BitBoards Manager reference for querying the bitboards
  bitboards::Manager &m_bitboards;

public:
  // force direct initialization
  explicit Board(bitboards::Manager &bitboards) : m_bitboards(bitboards) {}

  // Get a piece at the given position
  std::unique_ptr<pieces::Piece> getPieceAt(core::Position pos) const;
  // Check if a given position is unoccupied
  bool isEmpty(core::Position pos) const;
  // Check if a given position is occupied by a color
  bool isOccupiedBy(core::Position pos, core::Color color) const;
  
  // Place a piece at the position
  void placePiece(core::Position pos, core::PieceType type, core::Color color);
  // Remove a piece from a position
  void removePiece(core::Position pos);
  // Move a piece from a given position to a new one
  void movePiece(core::Position from, core::Position to);
};
} // namespace game