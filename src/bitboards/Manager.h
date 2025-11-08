/**
 * @file Manager.h
 * @brief BitBoard Manager class implementation
 *
 */
#pragma once

#include "BitBoard.h"
#include "core/Color.h"
#include "core/Constants.h"
#include "core/PieceType.h"
#include "core/Position.h"
#include <array>

namespace bitboards {
/**
 * @brief Manages BitBoards for all pieces
 *
 * Manager tracks all pieces' bitboards and
 * implements methods to manipulate them
 */
class Manager {
private:
  // All white pieces per piece type
  std::array<BitBoard, core::NUM_PIECE_TYPES> m_whitePieces;
  // All black pieces per piece type
  std::array<BitBoard, core::NUM_PIECE_TYPES> m_blackPieces;

  // All white pieces bitboard
  BitBoard m_whiteOccupancy;
  // All black pieces bitboard
  BitBoard m_blackOccupancy;

  // Update occupancy bitboards
  void updateOccupancy();

public:
  Manager() = default;
  // Retrieves BitBoard for a piece type of a color
  BitBoard getPieceBitBoard(core::Color color, core::PieceType type) const;
  // Retrieves BitBoard for all pieces occupancy of a color
  BitBoard getColorOccupancy(core::Color color) const;
  // Retrieves BitBoard for all pieces occupancy of all colors
  BitBoard getAllOccupancy() const;
  // Sets piece's position in a bitboard
  void setPiece(const core::Position &pos, core::Color color,
                core::PieceType type);
  // Clears piece's position in a bitboard
  void clearPiece(const core::Position &pos, core::Color color,
                  core::PieceType type);
  // Moves piece to a new location
  void movePiece(const core::Position &from, const core::Position &to,
                 core::Color color, core::PieceType type);
  // Clear all bitboards
  void clearAll();
};
} // namespace bitboards
