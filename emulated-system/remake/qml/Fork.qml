import QtQuick 2.14
import "qrc:/common"

Item {
    id: fork

    property alias orientation: displayedImage.orientation
    property Item base: parent

    implicitHeight: displayedImage.height
    implicitWidth: displayedImage.width

    anchors {
        horizontalCenter: base.horizontalCenter

        Binding on bottom {
            when: orientation === Orientation.Upward
            value: base.bottom
        }

        Binding on top {
            when: orientation === Orientation.Downward
            value: base.top
        }
    }

    OrientedImage {
        id: displayedImage

        source: "Fork.png"
    }
}
