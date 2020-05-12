import QtQuick 2.14

Item {
    id: trolley

    property bool position
    property int runwayLength
    property Item connection

    implicitHeight: displayedImage.height
    implicitWidth: displayedImage.width

    anchors.horizontalCenterOffset: {
        position ? runwayLength / 2 : -runwayLength / 2
    }

    Binding on anchors.centerIn {
        when: connection
        value: connection
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
