import QtQuick 2.3
import Custom 1.0
Item{
    id:root
    height:300
    width:300

    ContactsView{
        contactModel: QContactListModel{}
        width:parent.width
        height:parent.height
    }
}


