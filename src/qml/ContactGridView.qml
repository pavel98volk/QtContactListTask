import QtQuick 2.3


GridView {
    width: 180; height: 200

    model: ContactModel {}
    delegate: Text {
        text: name + ": " + number
    }
}