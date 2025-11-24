#pragma once

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

class PromotionDialog : public QDialog {
  Q_OBJECT

private:
  // Grid layout of the promotion buttons
  QGridLayout *m_pLayout;
  // Dialog title label
  QLabel *m_pTitleLabel;
  // Queen promotion
  QPushButton *m_pQueenButton;
  // Rook promotion
  QPushButton *m_pRookButton;
  // Bishop promotion
  QPushButton *m_pBishopButton;
  // Knight promotion
  QPushButton *m_pKnightButton;

  // Name of the selected piece
  QString m_strSelectedPiece;
  // Whether white promotes
  bool m_bIsWhite;

  // Setup UI components and layout
  void setupUI();
  // Create a piece button with icon
  void createPieceButton(QPushButton *&button, const QString &pieceName,
                         const QString &imagePath);

public:
  explicit PromotionDialog(bool isWhite, QWidget *parent = nullptr);

  // Promotion piece getter
  QString getSelectedPiece() const { return m_strSelectedPiece; }

private slots:
  // Handle promotion piece selection
  void onPieceSelected();
};