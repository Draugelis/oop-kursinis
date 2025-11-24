/**
 * @file GameWindow.cpp
 * @brief Game Window implementation
 */

#include "GameWindow.h"
#include "ui/style/ChessStyle.h"
#include "ui/style/UIConstants.h"

/**
 * @brief Construct a new Game Window object
 *
 * @param parent Parent widget
 */
GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent), m_pMainLayout(nullptr), m_pGameLayout(nullptr),
      m_pSidebarLayout(nullptr), m_pStatusBar(nullptr), m_pBoard(nullptr),
      m_pMoveHistory(nullptr), m_pControls(nullptr), m_pCentralWidget(nullptr),
      m_pBoardContainer(nullptr), m_pSidebarContainer(nullptr) {
  setupUI();
  connectSignals();

  setWindowTitle("Chess Game");
  resize(UIConstants::GAME_WINDOW_WIDTH, UIConstants::GAME_WINDOW_HEIGHT);
  // Disable resizing because I am too lazy to bother with responsive UI
  setFixedSize(UIConstants::GAME_WINDOW_WIDTH, UIConstants::GAME_WINDOW_HEIGHT);
}

/**
 * @brief Setup UI components
 *
 */
void GameWindow::setupUI() {
  // Set up central widget
  m_pCentralWidget = new QWidget(this);
  setCentralWidget(m_pCentralWidget);

  // Set up main vertical widget
  m_pMainLayout = new QVBoxLayout(m_pCentralWidget);
  m_pMainLayout->setSpacing(0);
  m_pMainLayout->setContentsMargins(0, 0, 0, 0);

  // Set up status bar
  m_pStatusBar = new StatusBarWidget(m_pCentralWidget);
  int statusBarHeight = static_cast<int>(UIConstants::GAME_WINDOW_HEIGHT *
                                         UIConstants::STATUS_BAR_HEIGHT_RATIO);
  m_pStatusBar->setFixedHeight(statusBarHeight);
  m_pMainLayout->addWidget(m_pStatusBar);

  // Set up horizontal game layout
  m_pGameLayout = new QHBoxLayout();
  m_pGameLayout->setSpacing(0);

  // Board container
  m_pBoardContainer = new QWidget(m_pBoardContainer);
  QVBoxLayout *boardContainerLayout = new QVBoxLayout(m_pBoardContainer);
  boardContainerLayout->setContentsMargins(
      UIConstants::BOARD_CONTAINER_MARGIN, UIConstants::BOARD_CONTAINER_MARGIN,
      UIConstants::BOARD_CONTAINER_MARGIN, UIConstants::BOARD_CONTAINER_MARGIN);

  m_pBoard = new BoardWidget(m_pBoardContainer);
  boardContainerLayout->addWidget(m_pBoard, 0, Qt::AlignCenter);
  m_pGameLayout->addWidget(m_pBoardContainer, 7); // 70% width

  // Set up side bar
  m_pSidebarContainer = new QWidget(m_pCentralWidget);
  m_pSidebarLayout = new QVBoxLayout(m_pSidebarContainer);
  m_pSidebarLayout->setSpacing(0);
  m_pSidebarLayout->setContentsMargins(0, 0, 0, 0);

  // Set up move history
  m_pMoveHistory = new MoveHistoryWidget(m_pSidebarContainer);
  m_pSidebarLayout->addWidget(m_pMoveHistory, 9); // 90% height

  // Game control buttons
  m_pControls = new GameControlsWidget(m_pSidebarContainer);
  m_pSidebarLayout->addWidget(m_pControls, 1); // 10% of height

  m_pGameLayout->addWidget(m_pSidebarContainer, 3); // 30% width

  m_pMainLayout->addLayout(m_pGameLayout);

  // Add background colors
  m_pCentralWidget->setStyleSheet(
      QString("background-color: %1;")
          .arg(ChessStyle::backgroundColor().name()));
  m_pBoardContainer->setStyleSheet(
      QString("background-color: %1;")
          .arg(ChessStyle::backgroundColor().name()));
}

/**
 * @brief Map child widget signals to window's signals
 */
void GameWindow::connectSignals() {
  // Forward board clicks
  connect(m_pBoard, &BoardWidget::squareClicked, this,
          &GameWindow::squareClicked);

  // Forward control button clicks
  connect(m_pControls, &GameControlsWidget::newGameClicked, this,
          &GameWindow::newGameClicked);
  connect(m_pControls, &GameControlsWidget::menuClicked, this,
          &GameWindow::menuClicked);
}

/**
 * @brief Get pointer to board widget
 *
 * @return BoardWidget* Pointer to board widget
 */
BoardWidget *GameWindow::getBoardWidget() { return m_pBoard; }

/**
 * @brief Get pointer to status bar widget
 *
 * @return StatusBarWidget* Pointer to status bar widget
 */
StatusBarWidget *GameWindow::getStatusBarWidget() { return m_pStatusBar; }

/**
 * @brief Get pointer to move history widget
 *
 * @return MoveHistoryWidget* Pointer to move history widget
 */
MoveHistoryWidget *GameWindow::getMoveHistoryWidget() { return m_pMoveHistory; }