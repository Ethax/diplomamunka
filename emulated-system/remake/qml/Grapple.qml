import QtQuick 2.14
import "qrc:/common"

Item {
    id: grapple

    property Item base: parent
    property alias orientation: displayedImage.orientation
    property bool open: false

    readonly property int upwardOffset: Math.round(base.height / 2.0)
    readonly property int downwardOffset: -upwardOffset

    implicitHeight: displayedImage.height
    implicitWidth: displayedImage.width

    anchors {
        horizontalCenter: base.horizontalCenter

        Binding on verticalCenterOffset {
            when: orientation === Orientation.Upward
            value: open ? upwardOffset : 0
        }

        Binding on verticalCenter {
            when: orientation === Orientation.Upward
            value: base.bottom
        }

        Binding on verticalCenterOffset {
            when: orientation === Orientation.Downward
            value: open ? downwardOffset : 0
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

        source: "qrc:/crane/Grapple.png"
    }
}
