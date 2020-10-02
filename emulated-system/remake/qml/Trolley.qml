import QtQuick 2.14

Item {
    id: trolley

    property Item base: parent
    property bool raised: false

    implicitHeight: displayedImage.height
    implicitWidth: displayedImage.width

    anchors {
        centerIn: base
        horizontalCenterOffset: raised ? base.width / 6 : -base.width / 6
    }

    Behavior on anchors.horizontalCenterOffset {
        NumberAnimation {
            easing.type: Easing.InOutCubic
            duration: 5000
        }
    }

    Image {
        id: displayedImage

        source: "qrc:/crane/Trolley.png"
    }
}
