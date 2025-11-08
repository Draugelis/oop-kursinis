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
  // BitBoard Manager for bitboard interactions
  bitboards::Manager m_bitboards;
  // Adapter for UI layer querying the board
  Board m_board;
  // Psedo-legal move generator
  MoveGenerator m_moveGenerator;
  // Move validation for filtering legal moves
  MoveValidator m_moveValidator;
  // Castling rights tracking
  CastlingRights m_castlingRights;
  // En Passant target position
  std::optional<core::Position> m_enPassantTarget;
  // Current turn
  core::Color m_sideToMove;
  // Half move counter for detecting draws by 50 move rule
  int m_nHalfMoveClock;
  // Full move counter
  int m_nFullMoveNumber;
  // Move history tracking
  std::vector<Move> m_moveHistory;
  // Game outcome/status
  GameOutcome m_gameOutcome;

  // Save the move
  void applyMove(const Move &move);
  // Update Castling Rights
  void updateCastlingRights(const Move &move);
  // Update En Passant Target
  void updateEnPassantTarget(const Move &move);
  // Change turn player
  void switchTurn();
  // Update half and full move counters
  void updateMoveCounter(const Move &move);
  // Update game status/outcome
  void updateOutcome();
  // Create move context object for move generation and validation
  MoveContext createMoveContext() const;

public:
  // Default constructor
  GameState();
  // Custom FEN constructor
  GameState(const std::string &fen);

  // Reset Game State to an initial default position
  void reset();
  // Reset Game State to an initial position with FEN
  void reset(const std::string &fen);
  // Populate board based on FEN (Forsyth-Edwards Notation).
  // See https://www.chess.com/terms/fen-chess
  void loadFEN(const std::string &fen);

  // Get mutable board reference
  Board &getBoard();
  // Get immutable board reference
  const Board &getBoard() const;
  // Get mutable castling rights
  CastlingRights &getCastlingRights();
  // Get immutable castling rights
  const CastlingRights &getCastlingRights() const;
  // Get current move color
  core::Color getSideToMove() const;
  // Get en passant target
  std::optional<core::Position> getEnPassantTarget() const;
  // Get half move clock value
  int getHalfMoveClock() const;
  // Get move number
  int getFullMoveNumber() const;
  // Get game outcome (or if it is still in progress)
  GameOutcome getOutcome() const;

  // Get legal moves for the whole board
  std::vector<Move> getLegalMoves() const;
  // Get legal moves from a position
  std::vector<Move> getLegalMovesFrom(core::Position pos) const;
  // Validate and execute the move
  bool tryMove(const Move &move);

  // Get move history
  const std::vector<Move> &getMoveHistory() const;
};
} // namespace game