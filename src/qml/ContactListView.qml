import QtQuick 2.3

ListView {
    clip: true
    delegate: Item{
        height:40
        width:parent?parent.width:0
        required property string name
        required property bool favourite
        required property color imageColor
        required property int imageHeadType

        Rectangle
        {
            id: background
            anchors.fill: parent
            color: "lightgreen"
            radius:5
            border.color:"white"
            border.width:2
        }
        Text {
            width:parent.width - 2*parent.height
            text: parent.name
            font.pixelSize: 20
            anchors.centerIn: parent
        }
        ContactImageView{
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            width:parent.height - 10
            height:parent.height -10

            backgroundColor:imageColor
            headType:imageHeadType
            circular:true
        }
        Image{
            visible:favourite
            height:parent.height
            source: "../resources/star.png"
            anchors.right:parent.right
            fillMode:Image.PreserveAspectFit
        }
        /*
        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onClicked: {
                if (mouse.button === Qt.RightButton)
                    contextMenu.popup()
            }
            onPressAndHold: {
                if (mouse.source === Qt.MouseEventNotSynthesized)
                    contextMenu.popup()
            }

            Item {
                id: contextMenu
                MenuItem { text: "Cut" }
                MenuItem { text: "Copy" }
                MenuItem { text: "Paste" }
            }
        }*/
    }
}
