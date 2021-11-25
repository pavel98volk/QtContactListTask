// main.qml
import QtQuick 2.3
import QtQuick.Layouts 1.15
import QtQuick.Window 2.3
import Custom 1.0
Item{
    id:root
    width:250
    height:300
    property var contactModel:QContactListModel{}
ColumnLayout{
    width: parent.width;
    height: parent.height;
    MenuView{
        model:root.contactModel
        Layout.preferredWidth:parent.width
        Layout.preferredHeight:30
        contact_presenter: stack_layout
    }
    StackLayout{
        id:stack_layout
        currentIndex: 0
        width:parent.width
        ContactListView{
            root: root
            width:parent.width
            model:root.contactModel
        }

        ContactGridView{
            width:parent.width
            height:parent.height
            model:root.contactModel
        }
    }
}
/*
FavouriteDialogView{
    name:"hello!"
    fav:true
    visible:true
}*/
}

