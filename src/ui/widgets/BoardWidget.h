#pragma once

#include "SquareWidget.h"
#include <QGridLayout>
#include <QWidget>
#include <vector>

class BoardWidget : public QWidget {
  Q_OBJECT; // Qt-specific macro

private:
  QGridLayout *m_pGridLayout;
  SquareWidget *m_pSquares[8][8];

  int m_nSelectedRow;
  int m_nSelectedCol;

  void createBoard();

private slots:
  void onSquareClicked(int row, int col);

public:
  explicit BoardWidget(QWidget *parent = nullptr);

  void setPiecePositions(const std::vector<std::vector<QString>> &positions);
  void setLegalMoveSquares(const std::vector<std::vector<bool>> &legalMoves);
  void clearSelection();
  void setSelectedSquare(int row, int col);

  QSize sizeHint() const override;
  QSize minimumSizeHint() const override;

signals:
  void squareClicked(int row, int col);
};