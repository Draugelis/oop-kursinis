/**
 * @file SquareView.qml
 * @brief Atomic square unit responsible for handling single square actions
 *
 */
import QtQuick 2.15

Rectangle {
    id: squareView

    // Square colors
    readonly property string darkColor: "#B58863"
    readonly property string lightColor: "#F0D9B5"
    readonly property string selectionOverlay: "#80b42589"
    readonly property string legalMoveIndicator: "#8000ff00"
    readonly property string legalCaptureIndicator: '#80ff0000'


    // Passed from BoardView
    property int row: 0
    property int col: 0
    property string pieceSvg: ""  // Path to piece image (empty = no piece)

    // Internal properties
    property bool isSelected: false
    property bool showLegalMove: false

    // Signal out
    signal squareClicked(int row, int col)

    // Dynamic size
    // Defaults to 80 if not set externally
    width: 80
    height: width  // Force height to match width

    // Set color based on the square row/col
    // Even row/col sum -> Dark square
    // Odd row/col sum -> Light square
    color: (row + col) % 2 === 0 ? darkColor : lightColor


    // Highlight if selected
    Rectangle {
        anchors.fill: parent
        color: selectionOverlay
        visible: isSelected
        z: 1 // Above base square
    }

    // Lighten the square when hovering over it using overlay square
    Rectangle {
        anchors.fill: parent
        color: '#33ffffff' // 20% transparency white
        visible: mouseArea.containsMouse
        z: 2 // Above selection
    }

    // Show dot for legal moves
    Rectangle {
        anchors.centerIn: parent
        // Show different colors if there's a piece on a target square
        color: pieceSvg !== "" ? legalCaptureIndicator : legalMoveIndicator
        width: parent.width * 0.3
        height: width
        radius: width / 2
        visible: showLegalMove
        z: 3 // Above hover
    }

    // Piece image
    Image {
        visible: pieceSvg !== ""
        anchors.centerIn: parent
        width: parent.width * 0.8 // 80% of the square
        height: parent.height * 0.8 // 80% of the square
        source: pieceSvg
        fillMode: Image.PreserveAspectFit
        z: 4 // Top layer
    }

    // Rank label (1-8); Display only on A file
    // Label position and color style is based on chess.com board where I tend to lose
    Text {
        visible: col === 0
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 4
        text: (8 - row).toString() // UI ranks are upside down so adjusting for that
        font.pixelSize: parent.height / 4 // 1/4 of the square size
        font.bold: true
        // Opposite color from a square
        color: (row + col) % 2 === 0 ? lightColor : darkColor
        z: 5 // Always on top
    }

    // File label (a-h); Display only on rank 1 (row 7 in this context)
    Text {
        visible: row === 7
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 4
        text: String.fromCharCode(97 + col) // Magic number 97 is an 'a' in ASCII table
        font.pixelSize: parent.height / 4 // 1/4 of the square size
        font.bold: true
        // Opposite color from a square
        color: (row + col) % 2 === 0 ? lightColor : darkColor
        z: 5 // Always on top
    }

    // Handle clicks
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: {
            console.log("Clicked square:", squareView.row, squareView.col)
            squareClicked(squareView.row, squareView.col) // Emit signal
        }
    }
}
