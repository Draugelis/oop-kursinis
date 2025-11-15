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
  Q_OBJECT;

private:
  // Layouts
  QVBoxLayout *m_pMainLayout;
  QHBoxLayout *m_pGameLayout;
  QVBoxLayout *m_pSidebarLayout;

  // Widgets
  StatusBarWidget *m_pStatusBar;
  BoardWidget *m_pBoard;
  MoveHistoryWidget *m_pMoveHistory;
  GameControlsWidget *m_pControls;

  // Containers
  QWidget *m_pCentralWidget;
  QWidget *m_pBoardContainer;
  QWidget *m_pSidebarContainer;

  void setupUI();
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