import QtQuick 2.14

Item {
    id: trolley

    property bool position: false
    property Item base: parent
    property int runwayLength: base.width / 3

    implicitHeight: displayedImage.height
    implicitWidth: displayedImage.width

    anchors {
        centerIn: base
        horizontalCenterOffset: position ? runwayLength / 2 : -runwayLength / 2
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
