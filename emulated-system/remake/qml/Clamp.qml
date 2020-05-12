import QtQuick 2.14

Item {
    id: clamp

    enum Orientation {
        Downward,
        Upward
    }

    property bool position
    property int runwayLength
    property int orientation
    property Item connection

    implicitHeight: displayedImage.height
    implicitWidth: displayedImage.width

    anchors.verticalCenterOffset: position ? runwayLength : 0

    Binding on anchors.horizontalCenter {
        when: connection
        value: connection.horizontalCenter
    }

    Binding on anchors.verticalCenter {
        when: connection && orientation === Clamp.Downward
        value: connection.top
    }

    Binding on anchors.verticalCenter {
        when: connection && orientation === Clamp.Upward
        value: connection.bottom
    }

    Behavior on anchors.verticalCenterOffset {
        NumberAnimation {
            duration: 2000
        }
    }

    Image {
        id: displayedImage

        source: "LeftClamp.png"

        Binding on rotation {
            when: orientation === Clamp.Downward
            value: 180
        }

        Binding on rotation {
            when: orientation === Clamp.Upward
            value: 0
        }
    }
}
