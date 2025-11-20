#include "Piece.h"

namespace pieces {

/**
 * @brief Constructs a new chess piece
 *
 * @param color core::Color of the piece (WHITE or BLACK)
 * @param type core::PieceType of the piece (PAWN, KNIGHT, BISHOP, ROOK, QUEEN,
 * KING)
 */
Piece::Piece(core::Color color, core::PieceType type)
    : m_color(color), m_type(type) {}

/**
 * @brief Piece color getter
 *
 * @return core::Color Color value for a piece
 */
core::Color Piece::getColor() const { return m_color; }

/**
 * @brief Piece type getter
 *
 * @return core::PieceType Piece type value for a piece
 */
core::PieceType Piece::getType() const { return m_type; }

/**
 * @brief Gets the algebraic notation letter for this piece
 *
 * @return char The uppercase letter representing this piece type
 */
char Piece::getLetter() const { return m_type.getLetter(); }
} // namespace pieces