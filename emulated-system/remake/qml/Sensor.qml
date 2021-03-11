import QtQuick 2.14
import "qrc:/body"

Item {
    id: sensor

    property bool active: false
    property color activeColor: "red"

    function detects(body) {
        return body.detectable && body.x < x + width && x < body.x + body.width
    }

    implicitHeight: parent.height + 5
    implicitWidth: 5

    anchors.verticalCenter: parent.verticalCenter

    Rectangle {
        id: displayedRectangle

        color: active ? activeColor : "grey"
        anchors.fill: parent
    }
}
