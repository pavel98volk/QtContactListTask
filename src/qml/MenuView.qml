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
        Item{

            Layout.fillHeight:true
            Layout.preferredWidth:parent.height
            Image{
                height: parent.height
                width: parent.height
                source: !menu_root.model.favOnly?"../resources/disabled_star.png": fav_ma.containsMouse?"../resources/crossed_star.png":"../resources/star.png"
                fillMode:Image.Stretch
                MouseArea {
                    id: fav_ma
                    enabled:true
                    hoverEnabled: true
                    anchors.fill: parent
                }
            }
            MouseArea {
                anchors.fill:parent
                onClicked: {
                    menu_root.model.favOnly = !menu_root.model.favOnly;
                }
            }
        }
        Item{
            Layout.fillHeight:true
            Layout.fillWidth: true
            TextInput{
                clip:true
                height:parent.height
                width:parent.width
                verticalAlignment:TextInput.AlignVCenter
                //text: model.search_string
                onTextChanged: model.search_string = text.toLowerCase()
                //font.capitalization: Font.AllUppercase
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
        Item{
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
