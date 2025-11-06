/**
 * @file Piece.h
 * @brief Abstract chess piece class
 *
 */

#pragma once

#include "bitboards/BitBoard.h"
#include "core/Color.h"
#include "core/PieceType.h"

namespace game {
class MoveContext;
}
namespace core {
class Position;
}

namespace pieces {
/**
 * @brief Abstract base class for chess pieces
 *
 * Defines the interface and properties for chess pieces including
 * color, type, and movement tracking. Each specific piece type
 * must inherit from this class and implement the move generation logic.
 *
 * @note This is an ABC (Abstract Base Class)
 * @see PieceFactory for creating concrete Piece instances
 */
class Piece {
protected:
  core::Color m_color;
  core::PieceType m_type;
  bool m_bHasMoved;

public:
  /**
   * @brief Constructs a new chess piece
   *
   * @param color core::Color of the piece (WHITE or BLACK)
   * @param type core::PieceType of the piece (PAWN, KNIGHT, BISHOP, ROOK,
   * QUEEN, KING)
   */
  Piece(core::Color color, core::PieceType type);
  // Virtual destructor
  virtual ~Piece() = default;

  // Get a piece color
  core::Color getColor() const;
  // Get a piece type
  core::PieceType getType() const;
  // Check if this piece has moved from its starting position
  bool hasMoved() const;
  // Get the algebraic notation letter for this piece
  char getLetter() const;

  // Mark piece as moved
  void setMoved();

  /**
   * @brief Generates a bitboard of all valid move destinations for this piece
   *
   * Virtual method that calculates all squares this piece can legally move
   * to from the given position.
   *
   * @param pos Current position of the piece on the board
   * @param context Current move context
   * @return BitBoard Bitboard with bits set for each valid destination square
   */
  virtual bitboards::BitBoard
  getMoveBitBoard(const core::Position &pos,
                  const game::MoveContext &context) const = 0;
};
} // namespace pieces