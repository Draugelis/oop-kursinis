#pragma once

#include "ui/widgets/BoardWidget.h"
#include "ui/widgets/GameControlsWidget.h"
#include "ui/widgets/MoveHistoryWidget.h"
#include "ui/widgets/StatusBarWidget.h"
#include <QHBoxLayout>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QWidget>

class GameWindow : public QMainWindow {
  Q_OBJECT

private:
  // Main layout
  QVBoxLayout *m_pMainLayout;
  // Board and sidebar layout
  QHBoxLayout *m_pGameLayout;
  QVBoxLayout *m_pSidebarLayout;

  // Status bar
  StatusBarWidget *m_pStatusBar;
  // Chess board
  BoardWidget *m_pBoard;
  // Move history
  MoveHistoryWidget *m_pMoveHistory;
  // Game control buttons
  GameControlsWidget *m_pControls;

  // Central container for all widgets
  QWidget *m_pCentralWidget;
  // Board container
  QWidget *m_pBoardContainer;
  // Side container (move history and controls)
  QWidget *m_pSidebarContainer;

  // Setup UI components
  void setupUI();
  // Map child widget signals to window's signals
  void connectSignals();

public:
  explicit GameWindow(QWidget *parent = nullptr);

  BoardWidget *getBoardWidget();
  StatusBarWidget *getStatusBarWidget();
  MoveHistoryWidget *getMoveHistoryWidget();

signals:
  void squareClicked(int row, int col);
  void newGameClicked();
  void menuClicked();
};