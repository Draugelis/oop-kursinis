/**
 * @file ChessGameController.h
 * @brief Game Controller responsible for bridging UI and the game engine
 */
#pragma once

#include "game/GameState.h"
#include "ui/windows/GameWindow.h"
#include <QObject>
#include <QString>
#include <memory>
#include <vector>

/**
 * @brief Controller bridging UI and game engine
 *
 * Connects GameWindow signals to GameState logic, manages piece
 * selection/movement. and updates UI based on game state
 */
class ChessGameController : public QObject {
  Q_OBJECT

private:
  // Game window pointer
  GameWindow *m_pGameWindow;
  // Game state instance
  std::unique_ptr<game::GameState> m_pGameState;

  // Selection state
  core::Position m_selectedPosition;
  bool m_bPieceSelected;

  // Update board display from game state
  void updateBoardDisplay();
  // Update status bar display
  void updateStatusDisplay();
  // Update move history display
  void updateMoveHistoryDisplay();
  // Convert board state to piece SVG paths
  std::vector<std::vector<QString>> convertBoardToPiecePaths();
  // Get legal moves for selected piece as 2D grid
  std::vector<std::vector<bool>> getLegalMovesForSelected();
  // Convert piece type and color to SVG path
  QString getPieceSvgPath(core::PieceType type, core::Color color) const;
  // Convert Move to algebraic notation
  QString moveToAlgebraic(const game::Move &move) const;
  // Handle pawn promotion dialog
  bool handlePromotion(game::Move &move);
    // Convert UI row to engine rank
  int uiRowToEngineRank(int row) const;
  // Convert engine rank to UI row
  int engineRankToUiRow(int rank) const;

public:
  explicit ChessGameController(GameWindow *gameWindow,
                               QObject *parent = nullptr);

  // Initialize new game
  void startNewGame();
  // Initialize new game from FEN
  void startNewGame(const QString &fen);

public slots:
  // Handle square click from board widget
  void handleSquareClick(int row, int col);
  // Handle new game button click
  void handleNewGame();
};