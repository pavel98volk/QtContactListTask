import QtQuick 2.3
import QtQuick.Layouts 1.15
Item {
    required property StackLayout contact_presenter
    RowLayout{
        width: parent.width;
        height: parent.height
        Column{
            Layout.fillHeight:true
            Layout.preferredWidth:parent.height
            Image{
                height: parent.height
                width: parent.height
                source: "../resources/star.png"
                fillMode:Image.Stretch
            }
        }
        Column{
            Layout.fillHeight:true
            Layout.fillWidth: true
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
        Column{
            Layout.fillHeight:true
            Layout.preferredWidth: parent.height
            anchors.right:parent.right
            Image{
                height: parent.height
                width: parent.height
                source: contact_presenter.currentIndex==0?"../resources/gridMenu.png":"../resources/listMenu.png"
                fillMode:Image.Stretch
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        contact_presenter.currentIndex^=1
                    }
                }
            }
        }

    }
}
