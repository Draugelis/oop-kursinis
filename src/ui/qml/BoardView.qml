/**
 * @file BoardView.qml
 * @brief Board view responsible for managing 8x8 square views
 *
 */
import QtQuick 2.15

Rectangle {
  id: boardView

  // Properties set externally
  property var piecePositions: []
  property var legalMoveSquares: [] // Set externally after selection

  // Internal properties
  property int selectedRow: -1
  property int selectedCol: -1

  // Out signal
  signal squareClicked(int row, int col)

  // Board dimension
  height: width

  Grid {
    // Standard chess board size
    rows: 8
    columns: 8

    Repeater {
      model: 64
      SquareView {
        // Set up square props
        row: Math.floor(index / 8)
        col: index % 8
        width: boardView.width / 8
        isSelected: (row === selectedRow && col === selectedCol)
        showLegalMove: (legalMoveSquares[row] && legalMoveSquares[row][col]) || false
        pieceSvg: (piecePositions[row] && piecePositions[row][col]) || ""
        onSquareClicked: {
          boardView.selectedRow = row
          boardView.selectedCol = col
          boardView.squareClicked(row, col)
        }
      }
    }
  }

}