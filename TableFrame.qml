import QtQuick 2.5

Item  {
    id: tableFrame
    width: 100
    height: 50
    property int dragStep: 20
    property alias headerColor: header.color
    property alias headerText: headerText.text
    property alias headerHeight: headerText.height

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
}
