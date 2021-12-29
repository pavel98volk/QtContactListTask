import QtQuick 2.0
import QtQuick.Layouts 1.15

Item {
    anchors.fill:parent;
    Rectangle{
        anchors.centerIn:parent
        anchors.fill:parent
        color: "green"
        ColumnLayout {
            anchors.fill:parent;

            //spacing: 20;
            ContactImageView{
                Layout.fillHeight:true
                Layout.preferredWidth:height;
                Layout.alignment: Qt.AlignCenter
                Layout.margins:30;
                backgroundColor:"#DDD" //imageColor
                headType:1 //imageHeadType
                circular:true
            }
            Rectangle{
                color:"#FFFFA7";
                Layout.fillWidth:true
                Layout.preferredHeight:40
                z:1
                Text {
                    Layout.alignment: Qt.AlignCenter;
                    text:"Caller Name Placeholder"
                    font.pixelSize: 20
                    anchors.centerIn: parent
                }
            }
            Rectangle{
                Layout.alignment: Qt.AlignCenter;
                color:"#F99";
                Layout.preferredHeight: 40;
                Layout.preferredWidth:100;
                z:1
                Text {
                    width:parent.width - 20;
                    text:"End Call"
                    font.pixelSize: 20
                    anchors.centerIn: parent
                }
            }

        }
    }

}
