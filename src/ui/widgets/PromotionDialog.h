#pragma once

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

class PromotionDialog : public QDialog {
  Q_OBJECT;

private:
  QGridLayout *m_pLayout;
  QLabel *m_pTitleLabel;
  QPushButton *m_pQueenButton;
  QPushButton *m_pRookButton;
  QPushButton *m_pBishopButton;
  QPushButton *m_pKnightButton;

  QString m_strSelectedPiece;
  bool m_bIsWhite;

  void setupUI();
  void createPieceButton(QPushButton *&button, const QString &pieceName,
                         const QString &svgPath);

public:
  explicit PromotionDialog(bool isWhite, QWidget *parent = nullptr);

  QString getSelectedPiece() const { return m_strSelectedPiece; }

private slots:
    void onPieceSelected();
};