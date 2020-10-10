import QtQuick 2.14

Row {
    default property alias delegate: repeater.delegate
    property int itemCount: 0

    function itemAt(index) {
        return repeater.itemAt(index)
    }

    function getItem(predicate) {
        for (var i = 0; i < itemCount; ++i) {
            if (predicate(itemAt(i))) {
                return itemAt(i)
            }
        }
        return undefined
    }

    Repeater {
        id: repeater

        model: itemCount
    }
}
