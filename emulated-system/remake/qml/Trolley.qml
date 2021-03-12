import QtQuick 2.14

Item {
    id: trolley

    property Item base: parent
    property bool raised: false

    readonly property int raisedPosition: Math.round(base.width / 6.0)
    readonly property int loweredPosition: -raisedPosition

    implicitHeight: displayedImage.height
    implicitWidth: displayedImage.width

    anchors {
        centerIn: base
        horizontalCenterOffset: raised ? raisedPosition : loweredPosition
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
