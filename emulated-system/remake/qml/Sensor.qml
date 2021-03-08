import QtQuick 2.14

Item {
    id: sensor

    property bool active: false
    property color activeColor: "red"

    function detects(item) {
        return item.x < x + width && x < item.x + item.width
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
