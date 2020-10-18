import QtQuick 2.14

Item {

    Image {
        id: base

        x: 120
        y: 100
        source: "WelderBase.png"
    }

    Item {
        id: name

        height: base.height
        width: base.width
        anchors.centerIn: base

        Rectangle {
            height: Math.abs(2 * anchors.topMargin) + arm.anchors.bottomMargin
                    - 10 //arm.y + arm.height - y - parent.height / 7.5
            width: parent.width / 3

            color: "black"

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.verticalCenter
            anchors.topMargin: -parent.height / 7.5
        }

        Image {
            id: arm

            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom

            source: "WelderArm.png"
            anchors.horizontalCenterOffset: 0
            anchors.bottomMargin: 10
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:3;height:480;width:640}
}
##^##*/

