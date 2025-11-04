#include "CastlingRights.h"

namespace game {

/**
 * @brief Construct a new Castling Rights object
 *
 * Default constructor where all rights are set to true
 */
CastlingRights::CastlingRights()
    : m_bWhiteKingSide(true), m_bWhiteQueenSide(true), m_bBlackKingSide(true),
      m_bBlackQueenSide(true) {}

/**
 * @brief Construct a new Castling Rights object
 *
 * @param whiteKingside Whether white can castle on king side
 * @param whiteQueenside Whether white can castle on queen side
 * @param blackKingside Whether black can castle on king side
 * @param blackQueenside Whether black can castle on queen side
 */
CastlingRights::CastlingRights(bool whiteKingside, bool whiteQueenside,
                               bool blackKingside, bool blackQueenside)
    : m_bWhiteKingSide(whiteKingside), m_bWhiteQueenSide(whiteQueenside),
      m_bBlackKingSide(blackKingside), m_bBlackQueenSide(blackQueenside) {}

/**
 * @brief Check if castling is allowed
 *
 * @param color Player's color
 * @param kingside Castling on the king side (false for queenside)
 * @return true If player can castle
 * @return false If player can't castle
 */
bool CastlingRights::canCastle(core::Color color, bool kingside) const {
  if (color == core::Color::WHITE) {
    return kingside ? m_bWhiteKingSide : m_bWhiteQueenSide;
  }
  return kingside ? m_bBlackKingSide : m_bBlackQueenSide;
}

/**
 * @brief Set castling rights for a color and side to false
 *
 * @param color Player's color
 * @param kingside Castling on the king side (false for queenside)
 */
void CastlingRights::revoke(core::Color color, bool kingside) {
  // Assign member to a right to reduce nesting in the method
  bool &right = (color == core::Color::WHITE)
                    ? (kingside ? m_bWhiteKingSide : m_bWhiteQueenSide)
                    : (kingside ? m_bBlackKingSide : m_bBlackQueenSide);
  right = false;
}

/**
 * @brief Check if color can castle on king side
 *
 * @param color Player's color
 * @return true If player can castle
 * @return false If player can't castle
 */
bool CastlingRights::canCastleKingside(core::Color color) const {
  return canCastle(color, true);
}

/**
 * @brief Check if color can castle on queen side
 *
 * @param color Player's color
 * @return true If player can castle
 * @return false If player can't castle
 */
bool CastlingRights::canCastleQueenside(core::Color color) const {
  return canCastle(color, false);
}

/**
 * @brief Set king side castling rights for a color to false
 *
 * @param color Player's color
 */
void CastlingRights::revokeKingside(core::Color color) { revoke(color, true); }

/**
 * @brief Set queen side castling rights for a color to false
 *
 * @param color Player's color
 */
void CastlingRights::revokeQueenside(core::Color color) {
  revoke(color, false);
}

/**
 * @brief Revoke all castling rights for a color
 *
 * @param color Player's color
 */
void CastlingRights::revokeAll(core::Color color) {
  revoke(color, true);
  revoke(color, false);
}
} // namespace game