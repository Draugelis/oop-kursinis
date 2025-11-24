#pragma once

#include "UIConstants.h"
#include <QColor>
#include <QFont>

namespace ChessStyle {
/**
 * @TODO: UPDATE COLORS USING A PROPER PALLETTE
 */

// General
inline QColor backgroundColor() { return QColor("#2f2f2f"); }
inline QColor textPrimary() { return QColor("#e0e0e0"); }
inline QColor textSecondary() { return QColor("#b0b0b0"); }
inline QColor border() { return QColor("#555555"); }

// Board colors
inline QColor lightSquare() { return QColor("#ebecd0"); }
inline QColor darkSquare() { return QColor("#739552"); }
inline QColor hoverColor() { return QColor("#ffffff15"); }
inline QColor selectedSquare() { return QColor("#f7f769"); }

// Legal move indicators
inline QColor legalMoveEmpty() { return QColor("#6c9d4280"); }
inline QColor legalMoveCapture() { return QColor("#cc3333cc"); }

// Status bar
inline QColor statusNormal() { return QColor("#e0e0e0"); }
inline QColor statusCheck() { return QColor("#e68a00"); }
inline QColor statusBackground() { return QColor("#3d3d3d"); }

// Buttons
inline QColor buttonNormal() { return QColor("#81b64c"); }
inline QColor buttonHover() { return QColor("#96c766"); }
inline QColor buttonPressed() { return QColor("#6c9d42"); }

// Move history
inline QColor moveHistoryEven() { return QColor("#3d3d3d"); }
inline QColor moveHistoryOdd() { return QColor("#353535"); }
inline QColor moveHistoryHighlight() { return QColor("#81b64c40"); }
inline QColor moveHistoryHeader() { return QColor("#4a4a4a"); }
inline QColor moveHistoryHeaderText() { return QColor("#b0b0b0"); } 

// Fonts
inline QFont standardFont(int size = UIConstants::FONT_SIZE_STANDARD) {
  return QFont("Press Start 2P", size);
}
inline QFont boldFont(int size = UIConstants::FONT_SIZE_STANDARD) {
  QFont font("Press Start 2P", size);
  font.setBold(true);
  return font;
}
} // namespace ChessStyle