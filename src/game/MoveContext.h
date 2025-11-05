/**
 * @file MoveContext.h
 * @brief Move context data class
 */
#pragma once

#include "core/Color.h"
#include "core/Position.h"
#include "game/CastlingRights.h"
#include <optional>

namespace game {
/**
 * @brief Combines game state parts needed for move generation
 *
 * Contains castling rights, en passant target, and side to move.
 * Passed to move generation methods to avoid passing multiple parameters
 */
class MoveContext {
private:
  // Castling Rights object reference
  const CastlingRights &m_castlingRights;
  // En Passant target piece
  std::optional<core::Position> m_enPassant;
  // Current color to move
  core::Color m_sideToMove;

public:
  // MoveContext constructor with all members to configure
  MoveContext(const CastlingRights &castling,
              std::optional<core::Position> enPassant, core::Color sideToMove);

  // Get Castling Rights reference
  const CastlingRights &getCastlingRights() const;
  // Get en passant target piece
  std::optional<core::Position> getEnPassant() const;
  // Get the color for the current move
  core::Color getSideToMove() const;
};
} // namespace game