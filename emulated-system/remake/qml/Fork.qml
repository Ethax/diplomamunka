import QtQuick 2.14
import "qrc:/common"

Item {
    id: fork

    property Item base: parent
    property alias orientation: displayedImage.orientation

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

        source: "qrc:/crane/Fork.png"
    }
}
