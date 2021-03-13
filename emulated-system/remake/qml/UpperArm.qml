import QtQuick 2.14

Item {
    id: upperArm

    property Item shoulder: parent
    property Item elbow: parent
    property real offset: 0.0

    implicitWidth: Math.round(elbow.width * 0.6)

    anchors {
        horizontalCenter: shoulder.horizontalCenter

        top: shoulder.verticalCenter
        topMargin: -Math.round(offset)

        bottom: elbow.bottom
        bottomMargin: Math.round(offset)
    }

    Rectangle {
        id: displayedRectangle

        color: "black"
        anchors.fill: parent
    }
}
