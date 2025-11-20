#pragma once

#include <QString>
#include <QWidget>

class SquareWidget : public QWidget {
  Q_OBJECT

private:
  // Square's row on the board
  int m_nRow;
  // Square's column on the board
  int m_nCol;

  // Path to piece's SVG file
  QString m_strPieceSvg;
  // Flag whether square is selected
  bool m_bIsSelected;
  // Flag whether square is hovered
  bool m_bIsHovered;
  // Flag whether to show legal move indicator
  bool m_bShowLegalMove;
  // Flag whether to show capture indicator
  bool m_bShowCapture;

  // Flag whether to show file label
  bool m_bShowFile;
  // Flag whether to show rank label
  bool m_bShowRank;

  // Draw square's background
  void drawBackground(QPainter &painter);
  // Draw piece on the square
  void drawPiece(QPainter &painter);
  // Draw selection indicator
  void drawSelection(QPainter &painter);
  // Draw legal move/capture indicators
  void drawLegalMoveIndicator(QPainter &painter);
  // Draw row/col labels
  void drawLabels(QPainter &painter);

protected:
  // Redraw the square
  void paintEvent(QPaintEvent *event) override;
  // Handle mouse clicks and emit signals
  void mousePressEvent(QMouseEvent *event) override;
  // Handle mouse hovering over the square
  void enterEvent(QEnterEvent *event) override;
  // Handle mouse no longer hovering over the square
  void leaveEvent(QEvent *event) override;

public:
  explicit SquareWidget(int row, int col, QWidget *parent = nullptr);

  // Get square's row
  int getRow() const;
  // Get square's column
  int getCol() const;
  // Check whether a square is selected
  bool isSelected() const;
  // Get piece SVG for a square
  QString getPieceSvg() const;

  // Square's piece SVG setter
  void setPieceSvg(const QString &svgPath);
  // Square's selected flag setter
  void setSelected(bool selected);
  // Square's legal move/capture indicator setter
  void setShowLegalMove(bool show, bool isCapture = false);
  // Should square show rank/file labels
  void setShowLabels(bool showFile, bool showRank);

  // Recommended square size
  QSize sizeHint() const override;
  // Recommended minimum square size
  QSize minimumSizeHint() const override;


signals:
  // Square click signal
  void squareClicked(int row, int col);
};
