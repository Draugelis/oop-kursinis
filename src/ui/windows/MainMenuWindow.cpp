/**
 * @file MainMenuWindow.cpp
 * @brief Main Menu Window implementation
 *
 */

#include "MainMenuWindow.h"
#include "ui/style/ChessStyle.h"
#include "ui/style/UIConstants.h"

/**
 * @brief Construct a new Main Menu Window object
 *
 * @param parent Parent widget
 */
MainMenuWindow::MainMenuWindow(QWidget *parent)
    : QMainWindow(parent), m_pMainLayout(nullptr), m_pCentralWidget(nullptr),
      m_pTitleLabel(nullptr), m_pStartButton(nullptr), m_pQuitButton(nullptr) {
  setupUI();
  setWindowTitle("Chess Game");
  resize(UIConstants::MAIN_MENU_WIDTH, UIConstants::MAIN_MENU_HEIGHT);
  // Disable resizing because I am too lazy to bother with responsive UI
  setFixedSize(UIConstants::MAIN_MENU_WIDTH, UIConstants::MAIN_MENU_HEIGHT);
}

/**
 * @brief Setup the UI components
 *
 */
void MainMenuWindow::setupUI() {
  // Set up central widget
  m_pCentralWidget = new QWidget(this);
  setCentralWidget(m_pCentralWidget);

  // Set up main layout
  m_pMainLayout = new QVBoxLayout(m_pCentralWidget);
  m_pMainLayout->setContentsMargins(
      UIConstants::MAIN_MENU_MARGIN, UIConstants::MAIN_MENU_MARGIN,
      UIConstants::MAIN_MENU_MARGIN, UIConstants::MAIN_MENU_MARGIN);
  m_pMainLayout->setSpacing(UIConstants::MAIN_MENU_SPACING);
  m_pMainLayout->addStretch(2); // center the content

  // Set up title label
  m_pTitleLabel = new QLabel("Chess Game", m_pCentralWidget);
  m_pTitleLabel->setFont(
      ChessStyle::standardFont(UIConstants::FONT_SIZE_TITLE));
  m_pTitleLabel->setAlignment(Qt::AlignCenter);
  m_pTitleLabel->setStyleSheet(
      QString("color: %1;").arg(ChessStyle::textPrimary().name()));
  m_pMainLayout->addWidget(m_pTitleLabel);
  m_pMainLayout->addSpacing(UIConstants::MAIN_MENU_TITLE_SPACING);

  // Set up Start Game button
  m_pStartButton = new QPushButton("Start Game", m_pCentralWidget);
  m_pStartButton->setMinimumSize(UIConstants::MAIN_MENU_BUTTON_MIN_WIDTH,
                                 UIConstants::MAIN_MENU_BUTTON_MIN_HEIGHT);
  m_pStartButton->setFont(ChessStyle::boldFont(UIConstants::FONT_SIZE_LARGE));
  applyButtonStyle(m_pStartButton);
  m_pMainLayout->addWidget(m_pStartButton);

  // Set up Quit button
  m_pQuitButton = new QPushButton("Quit", m_pCentralWidget);
  m_pQuitButton->setMinimumSize(UIConstants::MAIN_MENU_BUTTON_MIN_WIDTH,
                                UIConstants::MAIN_MENU_BUTTON_MIN_HEIGHT);
  m_pQuitButton->setFont(ChessStyle::boldFont(UIConstants::FONT_SIZE_LARGE));
  applyButtonStyle(m_pQuitButton);
  m_pMainLayout->addWidget(m_pQuitButton);

  m_pMainLayout->addStretch(3);

  // Connect buttons to signals
  connect(m_pStartButton, &QPushButton::clicked, this,
          &MainMenuWindow::startGameClicked);
  connect(m_pQuitButton, &QPushButton::clicked, this,
          &MainMenuWindow::quitClicked);

  // Add background color
  m_pCentralWidget->setStyleSheet(
      QString("background-color: %1;")
          .arg(ChessStyle::backgroundColor().name()));
}

/**
 * @brief Apply consistent button styling
 *
 * @param button Button to style
 */
void MainMenuWindow::applyButtonStyle(QPushButton *button) {
  button->setStyleSheet(QString("QPushButton {"
                                "    background-color: %1;"
                                "    color: %2;"
                                "    border: %3px solid %4;"
                                "    border-radius: %5px;"
                                "    padding: %6px %7px;"
                                "}"
                                "QPushButton:hover {"
                                "    background-color: %8;"
                                "    border: %9px solid %10;"
                                "}"
                                "QPushButton:pressed {"
                                "    background-color: %11;"
                                "}")
                            .arg(ChessStyle::buttonNormal().name())
                            .arg(ChessStyle::textPrimary().name())
                            .arg(UIConstants::BORDER_THIN)
                            .arg(ChessStyle::border().name())
                            .arg(UIConstants::BORDER_RADIUS_MEDIUM)
                            .arg(UIConstants::MAIN_MENU_BUTTON_PADDING)
                            .arg(UIConstants::MAIN_MENU_BUTTON_PADDING * 2)
                            .arg(ChessStyle::buttonHover().name())
                            .arg(UIConstants::BORDER_MEDIUM)
                            .arg(ChessStyle::textPrimary().name())
                            .arg(ChessStyle::buttonPressed().name()));
}