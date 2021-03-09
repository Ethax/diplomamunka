import QtQuick 2.14

Item {
    property int itemCount: 0
    property alias spacing: row.spacing
    default property alias delegate: repeater.delegate

    function itemAt(index) {
        return repeater.itemAt(index)
    }

    function findItem(predicate) {
        for (var i = 0; i < itemCount; ++i) {
            if (predicate(itemAt(i))) {
                return itemAt(i)
            }
        }
        return undefined
    }

    implicitHeight: row.height
    implicitWidth: row.width

    Row {
        id: row

        Repeater {
            id: repeater

            model: itemCount
        }
    }
}
