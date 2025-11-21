/**
 * @file SquareWidget.cpp
 * @brief Square Widget implementation with Qt
 */

#include "SquareWidget.h"
#include "core/Logging.h"
#include "ui/style/ChessStyle.h"
#include <QFile>
#include <QMouseEvent>
#include <QPainter>
#include <QSvgRenderer>

/**
 * @brief Construct a new Square Widget object
 *
 * @param row Square's row
 * @param col Square's column
 * @param parent Parent Widget
 */
SquareWidget::SquareWidget(int row, int col, QWidget *parent)
    : QWidget(parent), m_nRow(row), m_nCol(col), m_strPieceSvg(""),
      m_bIsSelected(false), m_bIsHovered(false), m_bShowLegalMove(false),
      m_bShowCapture(false), m_bShowFile(false), m_bShowRank(false) {
  // Enable hover events
  // See https://doc.qt.io/qt-6/qwidget.html#mouseTracking-prop
  setMouseTracking(true);
  // Set minimum square size
  // See https://doc.qt.io/qt-6/qwidget.html#minimumSize-prop
  setMinimumSize(minimumSizeHint());
}

/**
 * @brief Get square's row
 *
 * @return int Square's row
 */
int SquareWidget::getRow() const { return m_nRow; }

/**
 * @brief Get square's column
 *
 * @return int Square's row
 */
int SquareWidget::getCol() const { return m_nCol; }

/**
 * @brief Check whether a square is selected
 *
 * @return true If selected
 * @return false If not selected
 */
bool SquareWidget::isSelected() const { return m_bIsSelected; }

/**
 * @brief Get piece SVG for a square
 *

 * @return QString Path to SVG file
 */
QString SquareWidget::getPieceSvg() const { return m_strPieceSvg; }

/**
 * @brief Square's piece SVG setter
 *
 * @param svgPath Path to SVG file
 */
void SquareWidget::setPieceSvg(const QString &svgPath) {
  m_strPieceSvg = svgPath;
  update();
}

/**
 * @brief Square's selected flag setter
 *
 * @param selected Whether a square is selected
 */
void SquareWidget::setSelected(bool selected) {
  m_bIsSelected = selected;
  update();
}

/**
 * @brief Square's legal move/capture indicator setter
 *
 * @param show Whether to show legal move indicator
 * @param isCapture Whether the move is a capture
 */
void SquareWidget::setShowLegalMove(bool show, bool isCapture) {
  m_bShowLegalMove = (show && !isCapture);
  m_bShowCapture = (show && isCapture);
  update();
}

/**
 * @brief Should square show rank/file labels
 *
 * @param showFile Whether to show file label
 * @param showRank Whether to show rank label
 */
void SquareWidget::setShowLabels(bool showFile, bool showRank) {
  m_bShowFile = showFile;
  m_bShowRank = showRank;
  update();
}

/**
 * @brief Recommended square size hint
 *
 * @see https://doc.qt.io/qt-6/qwidget.html#sizeHint-prop
 * @return QSize Recommended square size
 */
QSize SquareWidget::sizeHint() const {
  return QSize(ChessStyle::preferredSquareSize(),
               ChessStyle::preferredSquareSize());
}

/**
 * @brief Recommended minimum square size hint
 *
 * @see https://doc.qt.io/qt-6/qwidget.html#minimumSizeHint-prop
 * @return QSize Recommended minimum square size
 */
QSize SquareWidget::minimumSizeHint() const {
  return QSize(ChessStyle::minSquareSize(), ChessStyle::minSquareSize());
}

/**
 * @brief Redraw the square
 *
 * @see https://doc.qt.io/qt-6/qwidget.html#paintEvent
 * @see https://stackoverflow.com/a/14105607
 * @param event Qt Paint Event pointer
 */
void SquareWidget::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing);

  drawBackground(painter);
  drawSelection(painter);
  drawLegalMoveIndicator(painter);
  drawPiece(painter);
  drawLabels(painter);
}

/**
 * @brief Handle mouse clicks and emit signals
 *
 * @see https://doc.qt.io/qt-6/qwidget.html#mousePressEvent
 * @param event Qt Mouse Press event pointer
 */
void SquareWidget::mousePressEvent(QMouseEvent *event) {
  // Act only on mouse left-click
  if (event->button() == Qt::LeftButton) {
    emit squareClicked(m_nRow, m_nCol);
  }
  // forward the event to the QPushButton
  // See https://stackoverflow.com/a/47466698
  QWidget::mousePressEvent(event);
}

/**
 * @brief Handle mouse hovering over the square
 *
 * @see https://doc.qt.io/qt-6/qwidget.html#enterEvent
 * @param event Qt Mouse enter the widget event
 */
void SquareWidget::enterEvent(QEnterEvent *event) {
  m_bIsHovered = true;
  update();
  QWidget::enterEvent(event);
}

/**
 * @brief Handle mouse no longer hovering over the square
 *
 * @see https://doc.qt.io/qt-6/qwidget.html#leaveEvent
 * @param event Qt Mouse leave the widget event
 */
void SquareWidget::leaveEvent(QEvent *event) {
  m_bIsHovered = false;
  update();
  QWidget::leaveEvent(event);
}

/**
 * @brief Draw square's background
 *
 * @param painter
 */
void SquareWidget::drawBackground(QPainter &painter) {
  // Colors are alternating so determining the base color
  QColor bgColor = ((m_nRow + m_nCol) % 2 == 0) ? ChessStyle::lightSquare()
                                                : ChessStyle::darkSquare();

  painter.fillRect(rect(), bgColor);

  // Hover efect
  if (m_bIsHovered && !m_bIsSelected) {
    painter.fillRect(rect(), ChessStyle::hoverColor());
  }
}

/**
 * @brief Draw selection indicator
 *
 * @param painter
 */
void SquareWidget::drawSelection(QPainter &painter) {
  if (m_bIsSelected) {
    painter.fillRect(rect(), ChessStyle::selectedSquare());
  }
}

/**
 * @brief Draw legal move/capture indicators
 *
 * @param painter
 */
void SquareWidget::drawLegalMoveIndicator(QPainter &painter) {
  if (!m_bShowLegalMove) {
    return; // nothing to draw
  }

  QColor indicatorColor = m_bShowCapture ? ChessStyle::legalMoveCapture()
                                         : ChessStyle::legalMoveEmpty();

  // Draw border for the moves
  QPen pen(indicatorColor, 4);
  painter.setPen(pen);
  painter.setBrush(Qt::NoBrush);
  painter.drawRect(rect().adjusted(2, 2, -2, -2)); // 2 px margins
}

/**
 * @brief Draw piece on the square
 *
 * @param painter
 */
void SquareWidget::drawPiece(QPainter &painter) {
  if (m_strPieceSvg.isEmpty()) {
    return; // nothing to draw
  }

  qCDebug(resourceDebug) << "Loading SVG:" << m_strPieceSvg
                         << "exists:" << QFile::exists(m_strPieceSvg);

  QSvgRenderer renderer(m_strPieceSvg);

  if (!renderer.isValid()) {
    qCWarning(resourceDebug) << "Invalid SVG renderer for:" << m_strPieceSvg;
    return;
  }

  QRect pieceRect = rect().adjusted(5, 5, -5, -5); // 5 px margins
  renderer.render(&painter, pieceRect);
}

/**
 * @brief Draw row/col labels
 *
 * @param painter
 */
void SquareWidget::drawLabels(QPainter &painter) {
  if (!m_bShowFile && !m_bShowRank) {
    return; // nothing to draw
  }

  // Opposite color than background
  QColor labelColor = ((m_nRow + m_nCol) % 2 == 0) ? ChessStyle::darkSquare()
                                                   : ChessStyle::lightSquare();

  painter.setPen(labelColor);
  painter.setFont(ChessStyle::standardFont(10));

  // File indicators are located on the bottom row
  if (m_bShowFile && m_nRow == 7) {
    char file = 'a' + m_nCol;
    painter.drawText(rect(), Qt::AlignBottom | Qt::AlignRight,
                     QString(file) + " ");
  }

  // Rank labels are located on the A file
  if (m_bShowRank && m_nCol == 0) {
    int rank = 8 - m_nRow; // UI and Chess engine ranks are numbered in reverse
                           // to each other
    painter.drawText(rect(), Qt::AlignTop | Qt::AlignLeft,
                     " " + QString::number(rank));
  }
}