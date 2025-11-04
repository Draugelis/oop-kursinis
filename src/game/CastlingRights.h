/**
 * @file CastlingRights.h
 * @brief State tracking for Castling rights
 */
#pragma once

#include "core/Color.h"

namespace game {
/**
 * @brief Value object for tracking king castling rights
 *
 */
class CastlingRights {
private:
  bool m_bWhiteKingSide;
  bool m_bWhiteQueenSide;
  bool m_bBlackKingSide;
  bool m_bBlackQueenSide;

  bool canCastle(core::Color color, bool kingside) const;
  void revoke(core::Color color, bool kingside);

public:
  CastlingRights();
  CastlingRights(bool whiteKingside, bool whiteQueenside, bool blackKingside,
                 bool blackQueenside);

  // Castling rights query methods
  bool canCastleKingside(core::Color color) const;
  bool canCastleQueenside(core::Color color) const;
  // Castling rights revokation methods
  void revokeKingside(core::Color color);
  void revokeQueenside(core::Color color);
  void revokeAll(core::Color color);
};
} // namespace game