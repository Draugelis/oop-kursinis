#include "MoveContext.h"

namespace game {
/**
 * @brief Construct a new Move Context object
 *
 * @param castling CastlingRights reference
 * @param enPassant En Passant target piece
 * @param sideToMove Which color's move
 */
MoveContext::MoveContext(const CastlingRights &castling,
                         std::optional<core::Position> enPassant,
                         core::Color sideToMove)
    : m_castlingRights(castling), m_enPassant(enPassant),
      m_sideToMove(sideToMove) {}

/**
 * @brief Return Castling Rights reference
 *
 * @return const CastlingRights&
 */
const CastlingRights &MoveContext::getCastlingRights() const {
  return m_castlingRights;
}

/**
 * @brief Return en passant target piece
 *
 * @return std::optional<core::Position>
 */
std::optional<core::Position> MoveContext::getEnPassant() const {
  return m_enPassant;
}

/**
 * @brief Return color for hte current move
 *
 * @return core::Color
 */
core::Color MoveContext::getSideToMove() const { return m_sideToMove; }

} // namespace game