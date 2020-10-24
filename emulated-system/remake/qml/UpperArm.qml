import QtQuick 2.14

Item {
    id: upperArm

    property Item base: parent
    property Item joint: parent
    property real offset: 0.0

    implicitWidth: Math.round(joint.width * 0.6)

    anchors {
        horizontalCenter: base.horizontalCenter

        top: base.verticalCenter
        topMargin: -Math.round(offset)

        bottom: joint.bottom
        bottomMargin: Math.round(offset)
    }

    Rectangle {
        id: displayedRectangle

        color: "black"
        anchors.fill: parent
    }
}
