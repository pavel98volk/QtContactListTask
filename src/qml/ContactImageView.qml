import QtQuick 2.3
import QtGraphicalEffects 1.0
Item {
    height:parent.height;
    width:parent.width;
    required property color backgroundColor
    required property int headType
    required property bool circular

    Rectangle{
        id:background_shape
        anchors.fill:parent;
        color:parent.backgroundColor
        anchors.left:parent.left
        radius:circular?width*0.5:0
        clip: true;
        z:1
    }
    Image{
        z:2
        anchors.fill:parent;
        verticalAlignment: Image.AlignVCenter
        source: "../resources/contact_img/body.png"
        fillMode:Image.PreserveAspectFit
        layer.enabled: true
        layer.effect: OpacityMask {
            maskSource: background_shape
        }
    }
    Image{
        z:2
        anchors.fill:parent;
        verticalAlignment: Image.AlignVCenter
        source: "../resources/contact_img/head/"+parent.headType+".png"
        fillMode:Image.PreserveAspectFit
        layer.enabled: true
        layer.effect: OpacityMask {
            maskSource: background_shape
        }
    }
}
