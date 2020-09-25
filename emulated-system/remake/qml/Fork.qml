import QtQuick 2.14

Item {
    id: fork

    property alias orientation: displayedImage.orientation
    property Item base: parent

    implicitHeight: displayedImage.height
    implicitWidth: displayedImage.width

    anchors {
        horizontalCenter: base.horizontalCenter

        Binding on bottom {
            when: orientation === OrientedImage.Upward
            value: base.bottom
        }

        Binding on top {
            when: orientation === OrientedImage.Downward
            value: base.top
        }
    }

    OrientedImage {
        id: displayedImage

        source: "Fork.png"
    }
}
