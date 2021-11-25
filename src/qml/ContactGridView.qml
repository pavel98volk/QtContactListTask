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
        required property var model
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
        MouseArea{
            id: buttonMouseArea
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onClicked: {
                if (mouse.button === Qt.RightButton) {
                    parent.rightButtonClick();
                } else if (mouse.button === Qt.LeftButton) {
                     parent.leftButtonClick();
                }
            }
        }
        signal leftButtonClick
        onLeftButtonClick:model.favourite = !model.favourite
        signal rightButtonClick;
        onRightButtonClick:{
            var dialog = Qt.createComponent("FavouriteDialogView.qml").createObject(this, {
                fav:favourite,
                name:name,
                parent:root,
                onSetFavourite: function(new_value){
                    model.favourite = new_value;
                }

            });
            dialog.setFavourite.connect((new_value)=>{model.favourite = new_value});
        }
    }
}
