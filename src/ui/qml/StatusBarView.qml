/**
 * @file StatusBarView.qml
 * @brief Simple status bar showing current turn and status
 *
 */
import QtQuick 2.15

Rectangle {
  id: statusBarView

  // Set externally
  property string currentTurn: "White" // White or Black
  property string currentStatus: "In Progress" // In Progress, Check, Checkmate, Stalemate, or Draw 

  // Size
  width: parent.width // 100% fill width
  height: parent.height * 0.10 // 10% of screen height

  // Colors
  readonly property string backgroundColor: "#666666"
  readonly property string textColor: "#d6d6d6"
  readonly property string warningTextColor: '#b95959'

  // Bar color
  color: backgroundColor

  // Turn indicator
  Text {
    text: "Turn: " + currentTurn.toUpperCase()
    // Font
    color: textColor
    font.pixelSize: parent.height * 0.6 // 60% of bar height
    font.bold: true
    // Positioning
    anchors.left: parent.left
    anchors.leftMargin: 20
    anchors.verticalCenter: parent.verticalCenter
  }

  // Status indicator
  Text {
    text: currentStatus.toUpperCase()
    // Font
    color: currentStatus.toUpperCase() === "CHECK" ? warningTextColor : textColor
    font.pixelSize: parent.height * 0.6 // 60% of bar height
    font.bold: true
    // Positioning
    anchors.right: parent.right
    anchors.rightMargin: 20
    anchors.verticalCenter: parent.verticalCenter
  }

}
