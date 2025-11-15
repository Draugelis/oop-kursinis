#pragma once

#include <QString>
#include <QWidget>

class SquareWidget : public QWidget {
private:
  // Position on board
  int m_nRow;
  int m_nCol;

  // Visual metadata
  QString m_strPieceSvg;
  bool m_bIsSelected;
  bool m_bIsHovered;
  bool m_bShowLegalMove;
  bool m_bShowCapture;

  // Labels on the side
  bool m_bShowFile;
  bool m_bShowRank;

  // Helpers
  void drawBackground(QPainter &painter);
  void drawPiece(QPainter &painter);
  void drawSelection(QPainter &painter);
  void drawLegalMoveIndicator(QPainter &painter);
  void drawLabels(QPainter &painter);

protected:
  // QWidget method overrides
  void paintEvent(QPaintEvent *pEvent) override;
  void mousePressEvent(QMouseEvent *pEvent) override;
  void enterEvent(QEnterEvent *pEvent) override;
  void leaveEvent(QEvent *pEvent) override;

public:
  explicit SquareWidget(int row, int col, QWidget *pParent = nullptr);

  // Getters
  int row() const { return m_nRow; }
  int col() const { return m_nCol; }
  int isSelected() const { return m_bIsSelected; }
  QString pieceSvg() const { return m_strPieceSvg; }

  // Setters
  void setPieceSvg(const QString &svgPath);
  void setSelected(bool selected);
  void setShowLegalMove(bool show, bool isCapture = false);
  void setShowLabels(bool showFile, bool showRank);

  // QWidget method overrides
  QSize sizeHint() const override;
  QSize minimumSizeHint() const override;

// Qt signals
signals:
  void squareClicked(int row, int col);
};

