import QtQuick 2.3



GridView{
    clip:true
    cellWidth: width/ Math.floor(width/100)
    cellHeight: width/ Math.floor(width/100)
    delegate:  Rectangle {
        required property string name
        required property bool favourite
        required property color imageColor
        required property int imageHeadType
        width: cellWidth
        height: cellHeight
        border{width: 2; color: "black"}
        color:"green"
        ContactImageView{
            anchors.fill: parent
            backgroundColor:imageColor
            headType:imageHeadType
            circular:false
        }
        Image{
            source:"../resources/star.png"
            anchors.right:parent.right
            anchors.top:parent.top
            visible:favourite
        }
    }
}

/*
GridView {
    cellHeight: 50
    cellWidth:  50
    model:
    delegate: Item {
        required property string name
        required property bool favourite
        required property color imageColor
        required property int imageHeadType
        ContactImageView{
            anchors.fill: parent
            backgroundColor:imageColor
            headType:imageHeadType
        }
    }
}

*/
