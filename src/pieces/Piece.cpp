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
 * @brief Checks if this piece has moved from its starting position
 *
 * Used for special move validation like castling orr pawn double-move
 *
 * @return true If piece has moved at least once
 * @return false If piece is still in starting position
 */
bool pieces::Piece::hasMoved() const { return m_bHasMoved; }

/**
 * @brief Gets the algebraic notation letter for this piece
 *
 * @return char The uppercase letter representing this piece type
 */
char pieces::Piece::getLetter() const { return m_type.getLetter(); }

/**
 * @brief Marks this piece as having moved
 *
 * Called after a piece is successfully moved. Prevents special
 * moves like castling or pawn double-move from being used after.
 */
void pieces::Piece::setMoved() { m_bHasMoved = true; }
