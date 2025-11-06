#include "Piece.h"

/**
 * @brief Piece color getter
 *
 * @return core::Color Color value for a piece
 */
core::Color pieces::Piece::getColor() const { return m_color; }

/**
 * @brief Piece type getter
 *
 * @return core::PieceType Piece type value for a piece
 */
core::PieceType pieces::Piece::getType() const { return m_type; }

/**
 * @brief Gets the algebraic notation letter for this piece
 *
 * @return char The uppercase letter representing this piece type
 */
char pieces::Piece::getLetter() const { return m_type.getLetter(); }
