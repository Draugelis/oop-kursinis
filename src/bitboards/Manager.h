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
  // Separate BitBoards for each color to denote occupancy for each piece type
  std::array<BitBoard, core::NUM_PIECE_TYPES> m_whitePieces;
  std::array<BitBoard, core::NUM_PIECE_TYPES> m_blackPieces;

  // Separate BitBoards for each color to denote color occupancy
  BitBoard m_whiteOccupancy;
  BitBoard m_blackOccupancy;

  void updateOccupancy();

public:
  Manager() = default;
  // Getters
  BitBoard getPieceBitBoard(core::Color color, core::PieceType type) const;
  BitBoard getColorOccupancy(core::Color color) const;
  BitBoard getAllOccupancy() const;
  // Setters
  void setPiece(const core::Position &pos, core::Color color,
                core::PieceType type);
  void clearPiece(const core::Position &pos, core::Color color,
                  core::PieceType type);
  void movePiece(const core::Position &from, const core::Position &to,
                 core::Color color, core::PieceType type);
};
} // namespace bitboards
