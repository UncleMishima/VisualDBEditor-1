import QtQuick 2.5
import QTableViewWrapper 1.0

Item  {
    id: tableFrame
    width: 100
    height: 50

    property int dragStep: 20
    property int yOffset: 0
    property alias tableView: tableView
    property alias headerColor: header.color
    property alias headerText: headerText.text
    property alias headerHeight: headerText.height
    property alias parentWidget: tableView.parentWidget
    property alias model: tableView.model

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

            // debug
            onDoubleClicked: tableView.show()
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
        y: tableFrame.y + headerHeight + yOffset
        width: tableFrame.width
        height: tableFrame.height - headerHeight
    }
}
