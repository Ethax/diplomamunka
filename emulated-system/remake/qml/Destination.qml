import QtQuick 2.14

Rectangle {
    property int number: 0

    width: 175
    height: 64
    color: "gray"

    Text {
        text: qsTr("C%1").arg(number)
        anchors.centerIn: parent

        color: "white"
        font {
            bold: true
            pointSize: 18
        }
    }
}
