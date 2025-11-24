/**
 * @file PromotionDialog.cpp
 * @brief Promotion Dialog implementation
 */

#include "PromotionDialog.h"
#include "QVBoxLayout"
#include "ui/style/ChessStyle.h"
#include "ui/style/UIConstants.h"

PromotionDialog::PromotionDialog(bool isWhite, QWidget *parent)
    : QDialog(parent), m_pLayout(nullptr), m_pTitleLabel(nullptr),
      m_pQueenButton(nullptr), m_pRookButton(nullptr), m_pBishopButton(nullptr),
      m_pKnightButton(nullptr), m_strSelectedPiece(""), m_bIsWhite(isWhite) {
  setupUI();

  // Set dialog modal to block game until user makes selects promotion piece
  setModal(true);
  setWindowTitle("Pawn Promotion");
}

/**
 * @brief Setup UI components and layout
 *
 */
void PromotionDialog::setupUI() {
  // Create base horizontal layout
  QVBoxLayout *baseLayout = new QVBoxLayout(this);

  // Title label
  m_pTitleLabel = new QLabel("Choose promotion piece:", this);
  m_pTitleLabel->setFont(ChessStyle::boldFont(UIConstants::FONT_SIZE_MEDIUM));
  m_pTitleLabel->setAlignment(Qt::AlignCenter);
  baseLayout->addWidget(m_pTitleLabel);

  // 2x2 grid layout for piece buttons
  m_pLayout = new QGridLayout();
  m_pLayout->setSpacing(UIConstants::PROMOTION_GRID_SPACING);

  // Create piece buttons with color in the name prefix
  QString colorPrefix = m_bIsWhite ? "w" : "b";
  createPieceButton(m_pQueenButton, "Queen",
                    QString(UIConstants::PIECE_IMG_PATH_TEMPLATE)
                        .arg(colorPrefix)
                        .arg("queen"));
  createPieceButton(m_pRookButton, "Rook",
                    QString(UIConstants::PIECE_IMG_PATH_TEMPLATE)
                        .arg(colorPrefix)
                        .arg("rook"));
  createPieceButton(m_pBishopButton, "Bishop",
                    QString(UIConstants::PIECE_IMG_PATH_TEMPLATE)
                        .arg(colorPrefix)
                        .arg("bishop"));
  createPieceButton(m_pKnightButton, "Knight",
                    QString(UIConstants::PIECE_IMG_PATH_TEMPLATE)
                        .arg(colorPrefix)
                        .arg("knight"));

  // Add buttons to grid (2x2 layout)
  m_pLayout->addWidget(m_pQueenButton, 0, 0);
  m_pLayout->addWidget(m_pRookButton, 0, 1);
  m_pLayout->addWidget(m_pBishopButton, 1, 0);
  m_pLayout->addWidget(m_pKnightButton, 1, 1);

  baseLayout->addLayout(m_pLayout);

  setLayout(baseLayout);

  // Set dialog size
  setFixedSize(UIConstants::PROMOTION_DIALOG_WIDTH,
               UIConstants::PROMOTION_DIALOG_HEIGHT);
}

/**
 * @brief Create a piece button with icon
 *
 * @param button Reference to button pointer to create
 * @param pieceName Name of the piece
 * @param svgPath Path to piece SVG icon
 */
void PromotionDialog::createPieceButton(QPushButton *&button,
                                        const QString &pieceName,
                                        const QString &svgPath) {
  // Set up button
  button = new QPushButton(this);
  button->setText(pieceName);
  button->setMinimumSize(UIConstants::PROMOTION_BUTTON_SIZE,
                         UIConstants::PROMOTION_BUTTON_SIZE);
  button->setIconSize(QSize(UIConstants::PROMOTION_ICON_SIZE,
                            UIConstants::PROMOTION_ICON_SIZE));

  QIcon icon(svgPath);
  button->setIcon(icon);

  // Add button style
  // TODO: move style sheets to ChessStyle
  button->setStyleSheet(QString("QPushButton {"
                                "    background-color: %1;"
                                "    border: %2px solid %3;"
                                "    border-radius: %4px;"
                                "    font-size: %5px;"
                                "    font-weight: bold;"
                                "}"
                                "QPushButton:hover {"
                                "    background-color: %6;"
                                "    border: %7px solid %8;"
                                "}"
                                "QPushButton:pressed {"
                                "    background-color: %9;"
                                "}")
                            .arg(ChessStyle::buttonNormal().name())
                            .arg(UIConstants::BORDER_THIN)
                            .arg(ChessStyle::border().name())
                            .arg(UIConstants::BORDER_RADIUS_MEDIUM)
                            .arg(UIConstants::FONT_SIZE_STANDARD)
                            .arg(ChessStyle::buttonHover().name())
                            .arg(UIConstants::BORDER_MEDIUM)
                            .arg(ChessStyle::textPrimary().name())
                            .arg(ChessStyle::buttonPressed().name()));

  // Connect to slot
  connect(button, &QPushButton::clicked, this,
          &PromotionDialog::onPieceSelected);
}

/**
 * @brief Handle piece selection
 *
 * Determines which button was clicked and closes the dialog
 */
void PromotionDialog::onPieceSelected() {
  QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());

  if (!clickedButton) {
    return; // no button was clicked
  }

  // Determine which piece was selected
  if (clickedButton == m_pQueenButton) {
    m_strSelectedPiece = "Queen";
  } else if (clickedButton == m_pRookButton) {
    m_strSelectedPiece = "Rook";
  } else if (clickedButton == m_pBishopButton) {
    m_strSelectedPiece = "Bishop";
  } else if (clickedButton == m_pKnightButton) {
    m_strSelectedPiece = "Knight";
  }

  // Close dialog with accept status
  accept();
}