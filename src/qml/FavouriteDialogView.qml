import QtQuick 2.3
import QtQuick.Layouts 1.15

Item{
    id:fav_dialog
    anchors.fill:parent
    required property string name
    required property bool fav
    signal setFavourite(bool new_value)

    Rectangle{
        anchors.centerIn:parent
        width:parent.width - 20
        height: parent.height - 20
        color:"#FAFAFA"
        border.color:"#4C4"
        border.width: 2
        radius: 5
        ColumnLayout{
            anchors.centerIn: parent
            width:parent.width
            Text {
                Layout.alignment:Qt.AlignHCenter
                horizontalAlignment: Text.AlignHCenter
                text: fav?"Remove \""+name+"\" from favourites?":"Add \""+name+"\" to favourites?"
                wrapMode: Text.WordWrap
                Layout.maximumWidth: parent.width
            }
            RowLayout{
                Layout.alignment:Qt.AlignHCenter
                Column{
                    width:50
                    Button{
                        width:50
                        height:30
                        text:"Yes"
                        onButtonClick:{
                            fav_dialog.setFavourite(!fav);
                            fav_dialog.destroy()
                        }

                    }
                }
                Column{
                    width:50
                    Button{
                        width:50
                        height:30
                        text:"No"
                        onButtonClick:{
                            fav_dialog.destroy()
                        }
                    }
                }
            }

        }


    }
}
