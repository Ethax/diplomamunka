import QtQuick 2.14

Row {
    default property alias delegate: repeater.delegate
    property int itemCount: 0

    function itemAt(index) {
        return repeater.itemAt(index)
    }

    function getItems() {
        var output = []

        for (var i = 0; i < itemCount; ++i) {
            output.push(itemAt(i))
        }

        return output
    }

    Repeater {
        id: repeater

        model: itemCount
    }
}
