import QtQuick 2.5
import QTableViewWrapper 1.0
import QtQuick.Controls 1.5

Item  {
    id: tableFrame
    width: 200
    height: 50

    property int dragStep: 20
    property int yOffset: 0
    property alias headerColor: header.color
    property alias headerText: headerText.text
    property alias headerHeight: headerText.height
    property alias parentWidget: tableView.parentWidget
    property alias model: tableView.model
    property alias tableView: tableView.tableView

    function show () {tableView.show()}

    Rectangle {
        id: header
        color: "grey"
        height: 50

        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        // debug
        ApplicationWindow {
            id: sizeEdit
            width: 100
            height: 100
            visible: false

            Slider {
                id: widthSlider
                stepSize: 1.0
                maximumValue: 1000
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.top: parent.top
                onValueChanged: tableFrame.width = value
            }

            Slider {
                id: heightSlider
                stepSize: 1.0
                maximumValue: 1000
                anchors.right: parent.right
                anchors.left: parent.left
                anchors.bottom: parent.bottom
                onValueChanged: tableFrame.height = value
            }

            Text {
                id: sizeText
                text: "w: " + tableFrame.width + " h: " + tableFrame.height
                fontSizeMode: Text.Fit
                elide: Text.ElideMiddle
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                anchors.fill: parent
                font.pixelSize: 12
            }
        }

        MouseArea {
            anchors.fill: parent

            drag.target: tableFrame
            drag.axis: Drag.XAndYAxis
            drag.minimumX: 0
            drag.minimumY: 0
            drag.maximumX: tableFrame.parent.width - tableFrame.width
            drag.maximumY: tableFrame.parent.height - tableFrame.height

            onMouseXChanged: {
                if (containsPress === true)
                    tableFrame.x = dragStep * (Math.floor(tableFrame.x / dragStep))
            }

            onMouseYChanged: {
                if (containsPress === true)
                    tableFrame.y = dragStep * (Math.floor(tableFrame.y / dragStep))
            }

            //debug
            onDoubleClicked: sizeEdit.visible = true
        }

        Text {
            id: headerText
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            fontSizeMode: Text.Fit
            text: "Text"
        }

    }

    QTableViewWrapper {
        id: tableView
        x: tableFrame.x
        y: tableFrame.y + header.height
        width: tableFrame.width
        height: tableFrame.height - headerHeight
    }
}
