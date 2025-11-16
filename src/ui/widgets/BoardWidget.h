#pragma once

#include "SquareWidget.h"
#include <QGridLayout>
#include <QWidget>
#include <vector>

/**
 * @brief Widget for 8x8 chess game board
 * 
 */
class BoardWidget : public QWidget {
  // Qt Meta-Object Compiler
  // https://doc.qt.io/qt-6/qobject.html#Q_OBJECT
  Q_OBJECT 

private :
  // Grid layout for presenting squares
  QGridLayout *m_pGridLayout;
  // Square widgets
  SquareWidget *m_pSquares[8][8];

  // Selected square's row
  int m_nSelectedRow;
  // Selected square's column
  int m_nSelectedCol;

  // Create 8x8 chess board grid layout
  void createBoard();
  // Update label display flags for the squares
  void updateSquareLabels();

private slots:
  // Handle square click events from child squares
  void onSquareClicked(int row, int col);

public:
  explicit BoardWidget(QWidget *parent = nullptr);

  // Set piece positions on the board
  void setPiecePositions(const std::vector<std::vector<QString>> &positions);
  // Set legal move indicators on the board
  void setLegalMoveSquares(const std::vector<std::vector<bool>> &legalMoves);
  // Clear all legal move indicators
  void clearLegalMoves();
  // Clear square selection
  void clearSelection();
  // Set selected square
  void setSelectedSquare(int row, int col);

  // Recommended board size hint
  QSize sizeHint() const override;
  // Recommended minimum board size hint
  QSize minimumSizeHint() const override;

signals:
  // Square click signal
  void squareClicked(int row, int col);
};