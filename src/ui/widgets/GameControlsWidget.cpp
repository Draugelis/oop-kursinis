/**
 * @file GameControlsWidget.cpp
 * @brief Game Controls Widget implementation
 */

#include "GameControlsWidget.h"
#include "ui/style/ChessStyle.h"

/**
 * @brief Construct a new Game Controls Widget object
 *
 * @param parent Parent widget
 */
GameControlsWidget::GameControlsWidget(QWidget *parent)
    : QWidget(parent), m_pLayout(nullptr), m_pNewGameButton(nullptr),
      m_pMenuButton(nullptr) {
  setupUI();
}

/**
 * @brief Setup the UI components and layout
 *
 */
void GameControlsWidget::setupUI() {
  // Create horizontal layout
  m_pLayout = new QHBoxLayout(this);
  m_pLayout->setContentsMargins(10, 10, 10, 10); // 10px margins
  m_pLayout->setSpacing(20);

  // Create buttons
  m_pNewGameButton = new QPushButton("New Game", this);
  m_pMenuButton = new QPushButton("Back to Menu", this);

  // Apply style
  applyButtonStyle(m_pNewGameButton);
  applyButtonStyle(m_pMenuButton);

  QSize minButtonSize(120, 40);
  m_pNewGameButton->setMinimumSize(minButtonSize);
  m_pMenuButton->setMinimumSize(minButtonSize);

  // Connect signals
  connect(m_pNewGameButton, &QPushButton::clicked, this,
          &GameControlsWidget::newGameClicked);
  connect(m_pMenuButton, &QPushButton::clicked, this,
          &GameControlsWidget::menuClicked);

  // Add buttons to layout
  m_pLayout->addStretch();
  m_pLayout->addWidget(m_pNewGameButton);
  m_pLayout->addWidget(m_pMenuButton);
  m_pLayout->addStretch();

  setLayout(m_pLayout);
}

/**
 * @brief Apply consistent styling
 *
 * @param button Button to style
 */
void GameControlsWidget::applyButtonStyle(QPushButton *button) {
  button->setStyleSheet(QString("QPushButton {"
                                "    background-color: %1;"
                                "    color: %2;"
                                "    border: none;"
                                "    border-radius: 5px;"
                                "    padding: 10px 20px;"
                                "    font-size: 14px;"
                                "    font-weight: bold;"
                                "}"
                                "QPushButton:hover {"
                                "    background-color: %3;"
                                "}"
                                "QPushButton:pressed {"
                                "    background-color: %4;"
                                "}")
                            .arg(ChessStyle::buttonNormal().name())
                            .arg(ChessStyle::textPrimary().name())
                            .arg(ChessStyle::buttonHover().name())
                            .arg(ChessStyle::buttonPressed().name()));
}

/**
 * @brief Recommended size
 * TODO: move these magic numbers to constants
 * @return QSize Recommended size
 */
QSize GameControlsWidget::sizeHint() const { return QSize(400, 60); }

/**
 * @brief Recommended minimum size
 * TODO: move these magic numbers to constants
 * @return QSize Minimum size
 */
QSize GameControlsWidget::minimumSizeHint() const { return QSize(300, 50); }