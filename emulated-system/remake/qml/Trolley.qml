import QtQuick 2.14

Item {
    id: trolley

    property bool position
    property int runwayLength
    property Item connection

    implicitHeight: displayedImage.height
    implicitWidth: displayedImage.width

    anchors {
        left: connection ? connection.left : undefined
        verticalCenter: connection ? connection.verticalCenter : undefined
        leftMargin: position ? runwayLength : 0
    }

    Behavior on anchors.leftMargin {
        NumberAnimation {
            easing.type: Easing.InOutCubic
            duration: 5000
        }
    }

    Image {
        id: displayedImage
        source: "Trolley.png"
    }
}
