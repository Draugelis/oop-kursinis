/**
 * @file GameControlsView.qml
 * @brief Control buttons for game actions
 *
 */
import QtQuick 2.15

Rectangle {
  id: controlsView

  // Signals
  signal newGameClicked()
  signal backToMenuClicked()

  // Colors
  readonly property string backgroundColor: "#666666"
  readonly property string buttonColor: "#a8c4e6"
  readonly property string buttonHoverColor: "#c0d8f0"
  readonly property string textColor: "#2c2c2c"

  color: backgroundColor

  // Buttons row
  Row {
    anchors.centerIn: parent
    width: parent.width * 0.90
    height: parent.height * 0.80
    spacing: 20

    // New Game Button
    Rectangle {
      id: newGameButton
      width: (parent.width - parent.spacing) / 2
      height: parent.height
      color: newGameMouseArea.containsMouse ? buttonHoverColor : buttonColor
      radius: 5

      Text {
        anchors.centerIn: parent
        text: "New Game"
        color: textColor
        font.pixelSize: Math.min(parent.width, parent.height) * 0.40
        font.bold: true
      }

      MouseArea {
        id: newGameMouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: controlsView.newGameClicked()
      }
    }

    // Back to Menu button
    Rectangle {
      id: backToMenuButton
      width: (parent.width - parent.spacing) / 2
      height: parent.height
      color: backToMenuMouseArea.containsMouse ? buttonHoverColor : buttonColor
      radius: 5

      Text {
        anchors.centerIn: parent
        text: "Back to Menu"
        color: textColor
        font.pixelSize: Math.min(parent.width, parent.height) * 0.40
        font.bold: true
      }

      MouseArea {
        id: backToMenuMouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: controlsView.backToMenuClicked()
      }
    }
  }
}