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
  // White can('t) castle on the king side
  bool m_bWhiteKingSide;
  // White can('t) castle on the queen side
  bool m_bWhiteQueenSide;
  // Black can('t) castle on the king side
  bool m_bBlackKingSide;
  // Black can('t) castle on the queen side
  bool m_bBlackQueenSide;

  // Check if color can castle on a side
  bool canCastle(core::Color color, bool kingside) const;
  // SeSet castling rights for a color and side to falset 
  void revoke(core::Color color, bool kingside);

public:
  // Constructor with all castling rights as true
  CastlingRights();
  // Constructor with custom castling rights
  CastlingRights(bool whiteKingside, bool whiteQueenside, bool blackKingside,
                 bool blackQueenside);

  // Check if color can castle on king side
  bool canCastleKingside(core::Color color) const;
  // Check if color can castle on queen side
  bool canCastleQueenside(core::Color color) const;
  // Set king side castling rights for a color to false
  void revokeKingside(core::Color color);
  // Set queen side castling rights for a color to false
  void revokeQueenside(core::Color color);
  // Revoke all castling rights for a color
  void revokeAll(core::Color color);
};
} // namespace game