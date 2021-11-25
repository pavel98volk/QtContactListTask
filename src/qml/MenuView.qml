import QtQuick 2.3
import QtQuick.Layouts 1.15
import Custom 1.0
Item {
    id:menu_root
    required property StackLayout contact_presenter
    required property QContactListModel model

    RowLayout{
        width: parent.width;
        height: parent.height
        Column{

            Layout.fillHeight:true
            Layout.preferredWidth:parent.height
            Image{
                height: parent.height
                width: parent.height
                source: !menu_root.model.headerData(0,Qt.Horizontal)?"../resources/star.png":"../resources/crossed_star.png"
                fillMode:Image.Stretch
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                   // NOT WORKING menu_root.model.setHeaderData(0Qt.Horizontal) = !menu_root.model.headerData(0,Qt.Horizontal);
                }
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
