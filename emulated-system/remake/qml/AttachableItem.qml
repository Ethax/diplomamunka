import QtQuick 2.14

Item {
    function attachTo(item) {
        var mappedPosition = parent.mapToItem(item, x, y)

        parent = item
        x = mappedPosition.x
        y = mappedPosition.y
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
