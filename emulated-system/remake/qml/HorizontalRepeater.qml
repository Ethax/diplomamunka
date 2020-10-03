import QtQuick 2.14

Row {
    default property alias delegate: repeater.delegate
    property int itemCount: 0

    function itemAt(index) {
        return repeater.itemAt(index)
    }

    Repeater {
        id: repeater

        model: itemCount
    }
}
