import QtQuick 2.5
import "DragFrame.js"

Item  {
    id: item
    width: 100
    height: 200
    property int dragStep: 20
    property alias headerColor: header.color
    property alias headerText: headerText.text
    property alias headerHeight: headerText.height
    property int resizingFrameWidth: 5

     Rectangle {
         id: header
         color: "grey"
         height: 50

		 anchors {
			top: parent.top
			topMargin: resizingFrameWidth

			left: parent.left
			leftMargin: resizingFrameWidth

			right: parent.right
			rightMargin: resizingFrameWidth
		 }

         MouseArea {
            anchors.fill: parent

            drag.target: item
            drag.axis: Drag.XAndYAxis
            drag.minimumX: 0
            drag.minimumY: 0
            drag.maximumX: item.parent.width - item.width
            drag.maximumY: item.parent.height - item.height

            onMouseXChanged: {
                if (containsPress === true)
                    item.x = dragStep * (Math.floor(item.x / dragStep))
            }

            onMouseYChanged: {
                if (containsPress === true)
                    item.y = dragStep * (Math.floor(item.y / dragStep))
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

     MouseArea {
         anchors.fill: parent
         property bool enableWidthChange: false
         property bool enableHeightChange: false

         onEntered: {

         }


     }
}
