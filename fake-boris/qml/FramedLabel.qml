import QtQuick 2.12

Rectangle {
    property alias text: underlyingText.text

    width: 30
    height: 20
    color: "#00000000"
    border.width: 1

    Text {
        id: underlyingText
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        anchors.fill: parent
    }
}
