/**
 * @file GameState.h
 * @brief Game state manager
 */
#pragma once

#include "bitboards/Manager.h"
#include "core/Color.h"
#include "core/Position.h"
#include "game/Board.h"
#include "game/CastlingRights.h"
#include "game/GameOutcome.h"
#include "game/Move.h"
#include "game/MoveContext.h"
#include "game/MoveGenerator.h"
#include "game/MoveValidator.h"
#include <optional>
#include <string>
#include <vector>

namespace game {
/**
 * @brief Manages complete chess game state and move execution
 *
 * GameState owns all game data and coordinates move generation, validation, and
 * execution. Implements methods for querying game status, generating and
 * applying legal moves
 */
class GameState {
private:
  bitboards::Manager m_bitboards;
  Board m_board;
  MoveGenerator m_moveGenerator;
  MoveValidator m_moveValidator;
  CastlingRights m_castlingRights;
  std::optional<core::Position> m_enPassantTarget;
  core::Color m_sideToMove;
  int m_nHalfMoveClock;
  int m_nFullMoveNumber;
  std::vector<Move> m_moveHistory;

  void applyMove(const Move &move);
  void updateCastlingRights(const Move &move);
  void updateEnPassantTarget(const Move &move);
  void switchTurn();
  void updateMoveCounter(const Move &move);
  GameOutcome calculateOutcome() const;
  MoveContext createMoveContext() const;

public:
  GameState();

  void reset();
  void loadFEN(const std::string &fen);

  Board &getBoard();
  const Board &getBoard() const;
  CastlingRights &getCastlingRights();
  const CastlingRights &getCastlingRights() const;
  core::Color getSideToMove() const;
  std::optional<core::Position> getEnPassantTarget() const;
  int getHalfMoveClock() const;
  int getFullMoveNumber() const;
  GameOutcome getOutcome() const;

  std::vector<Move> getLegalMoves() const;
  std::vector<Move> getLegalMovesFrom(core::Position pos) const;
  bool tryMove(const Move &move);

  const std::vector<Move> &getMoveHistory() const;
};
} // namespace game