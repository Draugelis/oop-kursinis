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

  bool canCastle(core::Color, bool kingside) const;
  void revoke(core::Color color, bool kingside);
public:
  CastlingRights();

  // Castling rights query methods
  bool canCastleKingside(core::Color color) const;
  bool canCastleQueenside(core::Color color) const;
  // Castling rights revokation methods
  void removeKingside(core::Color color);
  void removeQueenside(core::Color color);
  void removeAll(core::Color color);
};
} // namespace game