/**
 * @file MainMenuWindow.cpp
 * @brief Main Menu Window implementation
 *
 */

#include "MainMenuWindow.h"
#include "ui/style/ChessStyle.h"

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
  // TODO: move to constants
  resize(600, 400);
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
  m_pMainLayout->setContentsMargins(50, 50, 50, 50); // 50 px margins
  m_pMainLayout->setSpacing(30);
  m_pMainLayout->addStretch(2); // center the content

  // Set up title label
  m_pTitleLabel = new QLabel("Chess Game", m_pCentralWidget);
  m_pTitleLabel->setFont(ChessStyle::standardFont(48)); // TODO: change font
  m_pTitleLabel->setAlignment(Qt::AlignCenter);
  m_pTitleLabel->setStyleSheet(
      QString("color: %1;").arg(ChessStyle::textPrimary().name()));
  m_pMainLayout->addWidget(m_pTitleLabel);
  m_pMainLayout->addSpacing(50);

  // Set up Start Game button
  m_pStartButton = new QPushButton("Start Game", m_pCentralWidget);
  m_pStartButton->setMinimumSize(200, 60); // TODO: move to constants
  m_pStartButton->setFont(ChessStyle::boldFont(18));
  applyButtonStyle(m_pStartButton);
  m_pMainLayout->addWidget(m_pStartButton);

  // Set up Quit button
  m_pQuitButton = new QPushButton("Quit", m_pCentralWidget);
  m_pQuitButton->setMinimumSize(200, 60); // TODO: move to constants
  m_pQuitButton->setFont(ChessStyle::boldFont(18));
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
                                "    border: 2px solid %3;"
                                "    border-radius: 10px;"
                                "    padding: 15px 30px;"
                                "}"
                                "QPushButton:hover {"
                                "    background-color: %4;"
                                "    border: 3px solid %5;"
                                "}"
                                "QPushButton:pressed {"
                                "    background-color: %6;"
                                "}")
                            .arg(ChessStyle::buttonNormal().name())
                            .arg(ChessStyle::textPrimary().name())
                            .arg(ChessStyle::border().name())
                            .arg(ChessStyle::buttonHover().name())
                            .arg(ChessStyle::textPrimary().name())
                            .arg(ChessStyle::buttonPressed().name()));
}