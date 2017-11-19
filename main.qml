import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3

Item {
    id: root
    visible: true
    width: 1000
    height: 750

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
