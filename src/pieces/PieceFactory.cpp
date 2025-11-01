#include "PieceFactory.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

/**
 * @brief Factory method creating Piece instances
 *
 * @note This stackoverflow thread suggested unique pointers for factories:
 * https://stackoverflow.com/a/27302125
 *
 * @param color The color of the piece (WHITE or BLACK)
 * @param type core::PieceType of piece (PAWN, KNIGHT, BISHOP, ROOK, QUEEN,
 * KING)
 * @return std::unique_ptr<Piece> Unique pointer to a Piece class instance
 */
std::unique_ptr<pieces::Piece>
pieces::PieceFactory::createPiece(core::Color color, core::PieceType type) {
  switch (type) {
  case core::PieceType::PAWN:
    return std::make_unique<Pawn>(color);
  case core::PieceType::KNIGHT:
    return std::make_unique<Knight>(color);
  case core::PieceType::BISHOP:
    return std::make_unique<Bishop>(color);
  case core::PieceType::ROOK:
    return std::make_unique<Rook>(color);
  case core::PieceType::QUEEN:
    return std::make_unique<Queen>(color);
  case core::PieceType::KING:
    return std::make_unique<King>(color);
  default:
    return nullptr;
  }
}