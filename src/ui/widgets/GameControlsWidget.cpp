/**
 * @file GameControlsWidget.cpp
 * @brief Game Controls Widget implementation
 */

#include "GameControlsWidget.h"
#include "ui/style/ChessStyle.h"
#include "ui/style/UIConstants.h"

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
  m_pLayout->setContentsMargins(
      UIConstants::GAME_CONTROLS_MARGIN, UIConstants::GAME_CONTROLS_MARGIN,
      UIConstants::GAME_CONTROLS_MARGIN, UIConstants::GAME_CONTROLS_MARGIN);
  m_pLayout->setSpacing(UIConstants::GAME_CONTROLS_SPACING);

  // Create buttons
  m_pNewGameButton = new QPushButton("New Game", this);
  m_pMenuButton = new QPushButton("Back to Menu", this);

  // Apply style
  applyButtonStyle(m_pNewGameButton);
  applyButtonStyle(m_pMenuButton);

  QSize minButtonSize(UIConstants::GAME_CONTROLS_BUTTON_MIN_WIDTH,
                      UIConstants::GAME_CONTROLS_BUTTON_MIN_HEIGHT);
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
                                "    border-radius: %3px;"
                                "    padding: %4px %5px;"
                                "    font-size: %6px;"
                                "    font-weight: bold;"
                                "}"
                                "QPushButton:hover {"
                                "    background-color: %7;"
                                "}"
                                "QPushButton:pressed {"
                                "    background-color: %8;"
                                "}")
                            .arg(ChessStyle::buttonNormal().name())
                            .arg(ChessStyle::textPrimary().name())
                            .arg(UIConstants::BORDER_RADIUS_SMALL)
                            .arg(UIConstants::GAME_CONTROLS_BUTTON_PADDING)
                            .arg(UIConstants::GAME_CONTROLS_BUTTON_PADDING * 2)
                            .arg(UIConstants::FONT_SIZE_STANDARD)
                            .arg(ChessStyle::buttonHover().name())
                            .arg(ChessStyle::buttonPressed().name()));
}
/**
 * @brief Recommended size
 *
 * @return QSize Recommended size
 */
QSize GameControlsWidget::sizeHint() const {
  // Use parent layout to calculate sizing
  if (parentWidget()) {
    int parentWidth = parentWidget()->width();
    int parentHeight = parentWidget()->height();
    return QSize(parentWidth,
                 static_cast<int>(parentHeight *
                                  UIConstants::GAME_CONTROLS_HEIGHT_RATIO));
  }
  // Fallback
  return QSize(UIConstants::GAME_CONTROLS_FALLBACK_WIDTH,
               UIConstants::GAME_CONTROLS_FALLBACK_HEIGHT);
}

/**
 * @brief Recommended minimum size
 *
 * @return QSize Minimum size
 */
QSize GameControlsWidget::minimumSizeHint() const {
  return QSize(UIConstants::GAME_CONTROLS_MIN_WIDTH,
               UIConstants::GAME_CONTROLS_MIN_HEIGHT);
}