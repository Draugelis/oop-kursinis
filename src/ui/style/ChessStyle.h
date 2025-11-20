#pragma once

#include <QColor>
#include <QFont>

namespace ChessStyle {
/**
 * @TODO: UPDATE COLORS USING A PROPER PALLETTE
 */

// General
inline QColor backgroundColor() { return QColor("#fafafaff"); }
inline QColor textPrimary() { return QColor("#212121ff"); }
inline QColor textSecondary() { return QColor("#757575ff"); }
inline QColor border() { return QColor("#e0e0e0ff"); }

// Board colors
inline QColor lightSquare() { return QColor("#f0d9b5ff"); }
inline QColor darkSquare() { return QColor("#b58863ff"); }
inline QColor hoverColor() { return QColor("#e4e4e433"); }
inline QColor selectedSquare() { return QColor("#b4258980"); }

// Legal move indicators
inline QColor legalMoveEmpty() { return QColor("#00ff0080"); }
inline QColor legalMoveCapture() { return QColor("#ff000080"); }

// Status bar
inline QColor statusNormal() { return QColor("#323232ff"); }
inline QColor statusCheck() { return QColor("#dc143cff"); }
inline QColor statusBackground() { return QColor("#eceff1ff"); }

// Buttons
inline QColor buttonNormal() { return QColor("#add8e6ff"); }
inline QColor buttonHover() { return QColor("#87ceebff"); }
inline QColor buttonPressed() { return QColor("#6ca6cdff"); }

// Move history
inline QColor moveHistoryEven() { return QColor("#ffffffff"); }
inline QColor moveHistoryOdd() { return QColor("#f5f5f5ff"); }
inline QColor moveHistoryHighlight() { return QColor("#e3f2fdff"); }

// Fonts
inline QFont standardFont(int size = 14) { return QFont("Arial", size); }
inline QFont boldFont(int size = 14) {
  QFont font("Arial", size);
  font.setBold(true);
  return font;
}

// Size constants
inline constexpr int minSquareSize() { return 40; }
inline constexpr int preferredSquareSize() { return 80; }

} // namespace ChessStyle