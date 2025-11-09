/**
 * @file MoveHistoryView.qml
 * @brief Move history planel with moves in algebraic notation
 *
 */
import QtQuick 2.15

Rectangle {
  id: moveHistoryView

  // Set externally
  // Format [{number: 1, white: "e4", "black: "e5"}, ...]
  property var moveHistory: []

  // Size
  width: parent.width * 0.25 // 25% of the parent
  height: parent.height // Full height

  // Colors
  readonly property string backgroundColor: "#4d4d4d"
  readonly property string oddRowColor: "#5a5a5a"
  readonly property string evenRowColor: "#4d4d4d"
  readonly property string textColor: "#d6d6d6"
  readonly property string highlightColor: '#88a9f0'

  color: backgroundColor

  // Scrollable list
  ListView {
    id: listView
    anchors.fill: parent
    anchors.margins: 10
    clip: true  // contain within bounds
    
    model: moveHistory

    // Auto-scroll to the bottom when a new move is added
    onCountChanged: {
      Qt.callLater(function() {
        positionViewAtEnd()
      })
    }

    // Move row template
    delegate: Rectangle {
      width: listView.width
      height: 40

      // Alternate row colors for readability
      color: index % 2 === 0 ? evenRowColor : oddRowColor

      Row {
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        spacing: 10

        // Move number
        Text {
          width: parent.width * 0.2 // 20% of the row
          anchors.verticalCenter: parent.verticalCenter
          text: modelData.number + "."  // Nicer to have "2." than just "1"
          color: textColor
          font.pixelSize: parent.height * 0.8 // 80% of the row height
          font.bold: true
        }

        // White move
        Text {
          width: parent.width * 0.35 // 35% of the row
          anchors.verticalCenter: parent.verticalCenter
          text: modelData.white || ""
          color: isLastMove(index, "white") ? highlightColor : textColor // Highlight the last mvoe
          font.pixelSize: parent.height * 0.8 // 80% of the row height
          font.bold: isLastMove(index, "white")
        }

        // Black move
        Text {
          width: parent.width * 0.35 // 35% of the row
          anchors.verticalCenter: parent.verticalCenter
          text: modelData.white || ""
          color: isLastMove(index, "black") ? highlightColor : textColor // Highlight the last mvoe
          font.pixelSize: parent.height * 0.8 // 80% of the row height
          font.bold: isLastMove(index, "black")
        }
      }
    }
  }

  // Helper function to determine if a given move was a last one
  // God forgive me for writing javascript in a C++ OOP course work, Qt and my laziness made me do it
  function isLastMove(index, side) {
    if (moveHistory.length === 0) {
      return false;
    }

    var lastIndex = moveHistory.length - 1;
    if (index !== lastIndex) {
      return false;
    }

    var lastMove = moveHistory[lastIndex];
    // if black move exists, then it means black moved
    if (lastMove.black && side === "black") {
      return true;
    }

    // if black move doesn't exist, then it means white moved
    if (!lastMove.black && side === "white") {
      return true;
    }

    return false;
  }

}