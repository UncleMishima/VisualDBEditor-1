import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

Item {
    id: root
    visible: true
    width: 1000
    height: 750

    ToolBar {
        id: toolBar
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: parent.top

        RowLayout {
            anchors.fill: parent

            ToolButton {
                text: "Open"
            }
        }
    }

    Item {
        id: contentItem
        x: 55
        y: 165
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.top: toolBar.bottom
        anchors.bottom: statusBar.top

        // debug
        TableFrame {
            id: frame
            x: 200
            y: 200
            width: 315
            height: 180
            yOffset: toolBar.height
            parentWidget: quickWidget
            model: debugModel
        }

    }

    StatusBar {
        id: statusBar
        anchors.right: parent.right
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        RowLayout {
            anchors.fill: parent

            Text {
                id: widthAndHeightText
                text: "w: " + parent.width + " h: " + parent.height
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                fontSizeMode: Text.Fit
                font.pixelSize: 12
            }
        }
    }
}

