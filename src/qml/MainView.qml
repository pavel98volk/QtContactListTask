// main.qml
import QtQuick 2.3
import QtQuick.Layouts 1.15
import QtQuick.Window 2.3
import Custom 1.0
Item{
    width:250
    height:300
ColumnLayout{
    width: parent.width;
    height: parent.height;
    MenuView{
        Layout.preferredWidth:parent.width
        Layout.preferredHeight:30
        contact_presenter: stack_layout
    }
    StackLayout{
        id:stack_layout
        currentIndex: 0
        width:parent.width
        property var contactModel:QContactListModel{}
        ContactListView{
            width:parent.width
            model:parent.contactModel
        }

        ContactGridView{
            width:parent.width
            height:parent.height
            model:parent.contactModel
        }
    }
    //anchors.fill: parent
    //ContactGridView{}
}
}

