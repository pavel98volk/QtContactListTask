import QtQuick 2.3

Rectangle {
    id:button_id
    property string text:"Button"
    property color color:"#CFB"
    radius: 5
    border.color:Qt.darker(color,1.5)

    Gradient {
        id: lightGradient
        GradientStop { position: 0.0; color: button_id.color }
        GradientStop { position: 1.0; color: Qt.darker(button_id.color,1.5) }
    }

    Gradient {
        id: darkGradient
        GradientStop { position: 0.0; color: Qt.darker(button_id.color,1.7) }
        GradientStop { position: 1.0; color: Qt.darker(button_id.color,1.7) }
    }

    Rectangle{
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        Text{
            anchors.centerIn:parent
            id: buttonLabel
            font.pixelSize:20
            text: button_id.text
        }
    }

    signal buttonClick()

    MouseArea{
        id: buttonMouseArea
        anchors.fill: parent
        onClicked: parent.buttonClick()
        hoverEnabled: true

        onEntered:{
            parent.border.width= 2
        }

        onCanceled:{
            parent.border.width= 1
        }

        onExited: {
            parent.border.width= 1
        }
    }
    gradient: buttonMouseArea.pressed ? darkGradient : lightGradient
}
