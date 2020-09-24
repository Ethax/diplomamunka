import QtQuick 2.14

Item {
    id: clamp

    enum Orientation {
        Downward,
        Upward
    }

    property int orientation: Clamp.Upward
    property bool position: false
    property Item base: parent
    property int runwayLength: base.height / 2

    implicitHeight: displayedImage.height
    implicitWidth: displayedImage.width

    anchors {
        horizontalCenter: base.horizontalCenter
        verticalCenterOffset: position ? runwayLength : 0

        Binding on verticalCenter {
            when: orientation === Clamp.Downward
            value: base.top
        }

        Binding on verticalCenter {
            when: orientation === Clamp.Upward
            value: base.bottom
        }
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
