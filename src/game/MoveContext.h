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
  const CastlingRights &m_castlingRights;
  std::optional<core::Position> m_enPassant;
  core::Color m_sideToMove;

public:
  MoveContext(const CastlingRights &castling,
              std::optional<core::Position> enPassant, core::Color sideToMove);

  const CastlingRights &getCastlingRights() const;
  std::optional<core::Position> getEnPassant() const;
  core::Color getSideToMove() const;
};
} // namespace game