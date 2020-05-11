import QtQuick 2.14

Item {
    id: clamp

    property bool position
    property int runwayLength
    property Item connection

    // side: Left, Right
    implicitHeight: displayedImage.height
    implicitWidth: displayedImage.width

    anchors {
        horizontalCenter: trolley.horizontalCenter
        verticalCenter: trolley.bottom
        verticalCenterOffset: 0
    }

    Behavior on anchors.verticalCenterOffset {
        NumberAnimation {
            duration: 2000
        }
    }

    Image {
        id: displayedImage
        source: "LeftClamp.png"
    }
}
