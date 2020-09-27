import QtQuick 2.14

Item {
    property Item previousParent: parent

    function attachTo(item) {
        var newPoint = parent.mapToItem(item, x, y)

        previousParent = parent
        parent = item

        x = newPoint.x
        y = newPoint.y
    }

    function release() {
        attachTo(previousParent)
        previousParent = parent
    }

    function attachedTo(item) {
        return parent === item
    }

    function overlaps(item) {
        var thisRect = mapToItem(null, 0, 0, width, height)
        var otherRect = item.mapToItem(null, 0, 0, item.width, item.height)

        return thisRect.x < otherRect.x + otherRect.width
                && otherRect.x < thisRect.x + thisRect.width
                && thisRect.y < otherRect.y + otherRect.height
                && otherRect.y < thisRect.y + thisRect.height
    }
}
