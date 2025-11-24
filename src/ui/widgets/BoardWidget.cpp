/**
 * @file BoardWidget.cpp
 * @brief Chess Board Widget implementation
 */

#include "ui/widgets/BoardWidget.h"
#include "ui/style/UIConstants.h"

/**
 * @brief Construct a new Board Widget object
 *
 * @param parent Parent widget
 */
BoardWidget::BoardWidget(QWidget *parent)
    : QWidget(parent), m_pGridLayout(nullptr), m_nSelectedRow(-1),
      m_nSelectedCol(-1) {
  createBoard();
  updateSquareLabels();
}

/**
 * @brief Create 8x8 chess board grid layout
 *
 */
void BoardWidget::createBoard() {
  // Create a grid layout with no spacing
  m_pGridLayout = new QGridLayout(this);
  m_pGridLayout->setSpacing(0);
  m_pGridLayout->setContentsMargins(0, 0, 0, 0);

  // Create grid (nested array) of squares
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      SquareWidget *square = new SquareWidget(row, col, this);

      // Connect square's signal to the board slots
      // https://stackoverflow.com/a/32754353
      connect(square, &SquareWidget::squareClicked, this,
              &BoardWidget::onSquareClicked);

      // Add square to the grid layout
      m_pGridLayout->addWidget(square, row, col);
      m_pSquares[row][col] = square;
    }
  }

  setLayout(m_pGridLayout);
}

/**
 * @brief Update label display flags for the squares
 *
 */
void BoardWidget::updateSquareLabels() {
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      // Show file labels on the bottom row
      bool showFile = (row == 7);
      // Show rank labels on the left column
      bool showRank = (col == 0);
      m_pSquares[row][col]->setShowLabels(showFile, showRank);
    }
  }
}

/**
 * @brief Set piece positions on the board
 *
 * @param positions 8x8 vector of SVG file paths
 */
void BoardWidget::setPiecePositions(
    const std::vector<std::vector<QString>> &positions) {
  // Exit early if given vector doesn't have 8 rows of SVGs
  if (positions.size() != 8) {
    return;
  }

  for (int row = 0; row < 8; row++) {
    // Skip row if it doesn't have 8 columns
    if (positions[row].size() != 8) {
      continue;
    }

    for (int col = 0; col < 8; col++) {
      m_pSquares[row][col]->setPieceSvg(positions[row][col]);
    }
  }
}

/**
 * @brief Set legal move indicators on the board
 *
 * @param legalMoves 8x8 vector of bools indicating legal move for a selection
 */
void BoardWidget::setLegalMoveSquares(
    const std::vector<std::vector<bool>> &legalMoves) {
  // Exit early if given vector doesn't have 8 rows of SVGs
  if (legalMoves.size() != 8) {
    return;
  }

  for (int row = 0; row < 8; row++) {
    // Skip row if it doesn't have 8 columns
    if (legalMoves[row].size() != 8) {
      continue;
    }

    for (int col = 0; col < 8; col++) {
      bool isLegalMove = legalMoves[row][col];
      // Move is a capture, if it is legal on square with piece SVG
      bool isCapture =
          isLegalMove && !m_pSquares[row][col]->getPieceSvg().isEmpty();

      m_pSquares[row][col]->setShowLegalMove(isLegalMove, isCapture);
    }
  }
}

/**
 * @brief Clear all legal move indicators
 *
 */
void BoardWidget::clearLegalMoves() {
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      m_pSquares[row][col]->setShowLegalMove(false, false);
    }
  }
}

/**
 * @brief Clear square selection
 *
 */
void BoardWidget::clearSelection() {
  // If there's a selected square
  if (m_nSelectedRow >= 0 && m_nSelectedCol) {
    m_pSquares[m_nSelectedRow][m_nSelectedCol]->setSelected(false);
  }

  // -1 indicates no selection, just an arbitrary value outside 0-7 range
  m_nSelectedRow = -1;
  m_nSelectedCol = -1;
}

/**
 * @brief Set selected square
 *
 * @param row Selected square's row
 * @param col Selected square's column
 */
void BoardWidget::setSelectedSquare(int row, int col) {
  // Remove previous selection
  clearSelection();

  // Validate bounds; row/col must be within 0-7 range
  if (row < 0 || row >= 8 || col < 0 || col >= 8) {
    return;
  }

  m_nSelectedRow = row;
  m_nSelectedCol = col;
  m_pSquares[row][col]->setSelected(true);
}

/**
 * @brief Recommended board size hint
 *
 * @return QSize Recommended board size (square aspect ratio)
 */
QSize BoardWidget::sizeHint() const {
  int size = 8 * UIConstants::SQUARE_PREFERRED_SIZE;
  return QSize(size, size);
}

/**
 * @brief Recommended minimum board size hint
 *
 * @return QSize Minimum board size (square aspect ratio)
 */
QSize BoardWidget::minimumSizeHint() const {
  int size = 8 * UIConstants::SQUARE_MIN_SIZE;
  return QSize(size, size);
}

/**
 * @brief Handle square click events from child squares
 *
 * @param row Clicked square's row
 * @param col Clicked square's column
 */
void BoardWidget::onSquareClicked(int row, int col) {
  // Forward signal to parent
  emit squareClicked(row, col);
}