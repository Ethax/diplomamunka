import QtQuick 2.14

Item {
    id: trolley

    property bool position
    property int runwayLength
    property Item connection

    implicitHeight: displayedImage.height
    implicitWidth: displayedImage.width

    anchors {
        horizontalCenter: connection ? connection.horizontalCenter : undefined
        verticalCenter: connection ? connection.verticalCenter : undefined
        horizontalCenterOffset: (position ? runwayLength : -runwayLength) / 2
    }

    Behavior on anchors.horizontalCenterOffset {
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
