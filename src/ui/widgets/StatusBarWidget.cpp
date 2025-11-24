/**
 * @file StatusBarWidget.cpp
 * @brief Status Bar Widget implementation
 */

#include "StatusBarWidget.h"
#include "ui/style/ChessStyle.h"

/**
 * @brief Construct a new Status Bar Widget object
 *
 * @param parent Parent widget
 */
StatusBarWidget::StatusBarWidget(QWidget *parent)
    : QWidget(parent), m_pLayout(nullptr), m_pTurnLabel(nullptr),
      m_pStatusLabel(nullptr) {
  setupUI();
}

/**
 * @brief Setup UI components and layout
 *
 */
void StatusBarWidget::setupUI() {
  // Create horizontal layout
  m_pLayout = new QHBoxLayout(this);
  m_pLayout->setContentsMargins(UIConstants::STATUS_BAR_SIDE_MARGIN,
                                UIConstants::STATUS_BAR_VERTICAL_MARGIN,
                                UIConstants::STATUS_BAR_SIDE_MARGIN,
                                UIConstants::STATUS_BAR_VERTICAL_MARGIN);

  // Left: turn label
  m_pTurnLabel = new QLabel("Turn: White", this);
  m_pTurnLabel->setFont(ChessStyle::boldFont(UIConstants::FONT_SIZE_STANDARD));
  m_pTurnLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  m_pTurnLabel->setStyleSheet(
      QString("color: %1;").arg(ChessStyle::textPrimary().name()));

  // Right: game status label
  m_pStatusLabel = new QLabel("In Progress", this);
  m_pStatusLabel->setFont(
      ChessStyle::standardFont(UIConstants::FONT_SIZE_STANDARD));
  m_pStatusLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
  m_pStatusLabel->setStyleSheet(
      QString("color: %1;").arg(ChessStyle::statusNormal().name()));

  // Add labels to layout
  m_pLayout->addWidget(m_pTurnLabel);
  m_pLayout->addStretch(); // Create a gap between labels
  m_pLayout->addWidget(m_pStatusLabel);

  setLayout(m_pLayout);
}

/**
 * @brief Update status label color based on game state
 *
 * @param status Current game status
 */
void StatusBarWidget::updateStatusColor(const QString &status) {
  QColor color = (status == "Check" || status == "Checkmate")
                     ? ChessStyle::statusCheck()
                     : ChessStyle::statusNormal();

  m_pStatusLabel->setStyleSheet(QString("color: %1;").arg(color.name()));
}

/**
 * @brief Set current turn text
 *
 * @param turn Current turn (White or Black)
 */
void StatusBarWidget::setCurrentTurn(const QString &turn) {
  m_pTurnLabel->setText("Turn: " + turn);
}

/**
 * @brief Set game status text and update color
 *
 * @param status Game status (In Progress, Check, Checkmate, etc.)
 */
void StatusBarWidget::setGameStatus(const QString &status) {
  m_pStatusLabel->setText(status);
  updateStatusColor(status);
}

/**
 * @brief Recommended status bar size hint
 *
 * @return QSize
 */
QSize StatusBarWidget::sizeHint() const {
  // Use parent layout to calculate sizing
  if (parentWidget()) {
    return QSize(parentWidget()->width(),
                 static_cast<int>(UIConstants::GAME_WINDOW_HEIGHT *
                                  UIConstants::STATUS_BAR_HEIGHT_RATIO));
  }

  // Fallback
  return QSize(UIConstants::STATUS_BAR_FALLBACK_WIDTH,
               static_cast<int>(UIConstants::GAME_WINDOW_HEIGHT *
                                UIConstants::STATUS_BAR_HEIGHT_RATIO));
}
/**
 * @brief Recommended minimum status bar size hint
 *
 * @return QSize
 */
QSize StatusBarWidget::minimumSizeHint() const {
  return QSize(UIConstants::STATUS_BAR_MIN_WIDTH,
               static_cast<int>(UIConstants::GAME_WINDOW_HEIGHT *
                                UIConstants::STATUS_BAR_HEIGHT_RATIO));
}