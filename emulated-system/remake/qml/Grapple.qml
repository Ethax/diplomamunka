import QtQuick 2.14
import "qrc:/common"

Item {
    id: grapple

    property alias orientation: displayedImage.orientation
    property bool position: false
    property Item base: parent
    property int runwayLength: base.height / 2

    implicitHeight: displayedImage.height
    implicitWidth: displayedImage.width

    anchors {
        horizontalCenter: base.horizontalCenter

        Binding on verticalCenterOffset {
            when: orientation === Orientation.Upward
            value: position ? runwayLength : 0
        }

        Binding on verticalCenter {
            when: orientation === Orientation.Upward
            value: base.bottom
        }

        Binding on verticalCenterOffset {
            when: orientation === Orientation.Downward
            value: position ? -runwayLength : 0
        }

        Binding on verticalCenter {
            when: orientation === Orientation.Downward
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

        source: "Grapple.png"
    }
}
