import QtQuick 2.14

Item {
    id: clamp

    property alias orientation: displayedImage.orientation
    property bool position: false
    property Item base: parent
    property int runwayLength: base.height / 2

    implicitHeight: displayedImage.height
    implicitWidth: displayedImage.width

    anchors {
        horizontalCenter: base.horizontalCenter

        Binding on verticalCenterOffset {
            when: orientation === OrientedImage.Upward
            value: position ? runwayLength : 0
        }

        Binding on verticalCenter {
            when: orientation === OrientedImage.Upward
            value: base.bottom
        }

        Binding on verticalCenterOffset {
            when: orientation === OrientedImage.Downward
            value: position ? -runwayLength : 0
        }

        Binding on verticalCenter {
            when: orientation === OrientedImage.Downward
            value: base.top
        }
    }

    Behavior on anchors.verticalCenterOffset {
        NumberAnimation {
            duration: 2000
        }
    }

    OrientedImage {
        id: displayedImage

        source: "Clamp.png"
    }
}
