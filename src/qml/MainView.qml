// main.qml
import QtQuick 2.3
import QtQuick.Layouts 1.15
import QtQuick.Window 2.3
import Custom 1.0
//Image { source: "../resources/contact_img/body.png" }
//Image { source: "../resources/contact_img/body.png" }

Item{
    width:250
    height:300
ColumnLayout{
    width: parent.width;
    height: parent.height;
    Item{
        height:30
        width:parent.width
        RowLayout{
           height:parent.height
           width:parent.width
            Column{
                Layout.preferredHeight:parent.height
                Layout.preferredWidth: parent.height
                Image{
                    height: parent.height
                    width: parent.height
                    source: "../resources/star.png"
                    fillMode:Image.Stretch
                }
            }
            Column{
                Layout.preferredHeight:parent.height
                Layout.preferredWidth: parent.width /2
                TextInput{
                    clip:true
                    height:parent.height
                    width:parent.width
                    verticalAlignment:TextInput.AlignVCenter
                    Text{
                        height: parent.height;
                        width: parent.width
                        text:"search..."
                        color:"#aaa"
                        visible:!parent.text
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }
        }
    }

    StackLayout{
        currentIndex: 0
        width:parent.width
        ContactListView{
            width:parent.width
            model:QContactListModel{}
        }
        //ContactGridView{}
    }
    //anchors.fill: parent
    //ContactGridView{}
}
}

