/**
 * @file MoveHistoryWidget.cpp
 * @brief Move History Widget implementation
 */

#include "MoveHistoryWidget.h"
#include "ui/style/ChessStyle.h"

/**
 * @brief Construct a new Move History Widget object
 *
 * @param parent Parent widget
 */
MoveHistoryWidget::MoveHistoryWidget(QWidget *parent)
    : QWidget(parent), m_pLayout(nullptr), m_pTableWidget(nullptr) {
  setupUI();
}

/**
 * @brief Setup UI components and layout
 *
 */
void MoveHistoryWidget::setupUI() {
  // Create base vertical layout
  m_pLayout = new QVBoxLayout(this);
  m_pLayout->setContentsMargins(
      UIConstants::MOVE_HISTORY_MARGIN, UIConstants::MOVE_HISTORY_MARGIN,
      UIConstants::MOVE_HISTORY_MARGIN, UIConstants::MOVE_HISTORY_MARGIN);
  m_pLayout->setSpacing(0);

  // Create and set up table widget
  m_pTableWidget = new QTableWidget(this);
  m_pTableWidget->setColumnCount(3); // move number, white move, black move
  m_pTableWidget->setHorizontalHeaderLabels({"#", "White", "Black"});

  // Set up column widths
  m_pTableWidget->horizontalHeader()->setStretchLastSection(false);
  m_pTableWidget->setColumnWidth(0,
                                 UIConstants::MOVE_HISTORY_MOVE_NUMBER_WIDTH);
  m_pTableWidget->horizontalHeader()->setSectionResizeMode(0,
                                                           QHeaderView::Fixed); // disable resize
  m_pTableWidget->horizontalHeader()->setSectionResizeMode(
      1, QHeaderView::Stretch);
  m_pTableWidget->horizontalHeader()->setSectionResizeMode(
      2, QHeaderView::Stretch);

  // Disable editing
  m_pTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

  // Enable row selection
  m_pTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
  m_pTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

  // Enable alternating row colors
  m_pTableWidget->setAlternatingRowColors(true);

  m_pTableWidget->setStyleSheet(
      QString("QTableWidget {"
              "    background-color: %1;"
              "    alternate-background-color: %2;"
              "    selection-background-color: %3;"
              "    gridline-color: %4;"
              "    border: 1px solid %4;"
              "}"
              "QHeaderView::section {"
              "    background-color: %5;"
              "    color: %6;"
              "    padding: %7px;"
              "    border: none;"
              "    font-weight: bold;"
              "}")
          .arg(ChessStyle::moveHistoryEven().name())
          .arg(ChessStyle::moveHistoryOdd().name())
          .arg(ChessStyle::moveHistoryHighlight().name())
          .arg(ChessStyle::border().name())
          .arg(ChessStyle::moveHistoryHeader().name())
          .arg(ChessStyle::moveHistoryHeaderText().name())
          .arg(UIConstants::MOVE_HISTORY_MARGIN));

  // Hide row numbers
  m_pTableWidget->verticalHeader()->setVisible(false);

  m_pLayout->addWidget(m_pTableWidget);

  setLayout(m_pLayout);
}

/**
 * @brief Rebuild table from move vector
 *
 */
void MoveHistoryWidget::rebuildTable() {
  // Get number of required rows
  int numRows = (m_moves.size() + 1) / 2;
  m_pTableWidget->setRowCount(numRows);

  // Populate table
  for (size_t i = 0; i < m_moves.size(); i++) {
    int row = i / 2;
    int col = (i % 2) + 1; // 1 for white, 2 for black

    // Add move number if white's move
    if (col == 1) {
      QTableWidgetItem *numItem =
          new QTableWidgetItem(QString::number(row + 1));
      numItem->setTextAlignment(Qt::AlignCenter);
      m_pTableWidget->setItem(row, 0, numItem);
    }

    QTableWidgetItem *moveItem = new QTableWidgetItem(m_moves[i]);
    moveItem->setTextAlignment(Qt::AlignCenter);
    m_pTableWidget->setItem(row, col, moveItem);
  }
}

/**
 * @brief Scroll to bottom of table to show latest move
 *
 */
void MoveHistoryWidget::scrollToBottom() { m_pTableWidget->scrollToBottom(); }

/**
 * @brief Add a move to the history
 *
 * @param move Move notation string
 */
void MoveHistoryWidget::addMove(const QString &move) {
  m_moves.push_back(move);
  rebuildTable();
  scrollToBottom();
}

/**
 * @brief Set all moves
 *
 * @param moves Vector of move notation string
 */
void MoveHistoryWidget::setMoves(const std::vector<QString> &moves) {
  m_moves = moves;
  rebuildTable();
  scrollToBottom();
}

/**
 * @brief Clear whole move history
 *
 */
void MoveHistoryWidget::clearHistory() {
  m_moves.clear();
  m_pTableWidget->setRowCount(0);
}

/**
 * @brief Recommended size hint
 *
 * @return QSize Recommended size
 */
QSize MoveHistoryWidget::sizeHint() const {
  // Use parent layout to calculate sizing
  if (parentWidget()) {
    int parentWidth = parentWidget()->width();
    int parentHeight = parentWidget()->height();
    return QSize(parentWidth,
                 static_cast<int>(parentHeight *
                                  UIConstants::MOVE_HISTORY_HEIGHT_RATIO));
  }
  // Fallback
  return QSize(UIConstants::MOVE_HISTORY_FALLBACK_WIDTH,
               UIConstants::MOVE_HISTORY_FALLBACK_HEIGHT);
}

/**
 * @brief Recommended minimum size hint
 *
 * @return QSize Minimum size
 */
QSize MoveHistoryWidget::minimumSizeHint() const {
  return QSize(UIConstants::MOVE_HISTORY_MIN_WIDTH,
               UIConstants::MOVE_HISTORY_MIN_HEIGHT);
}