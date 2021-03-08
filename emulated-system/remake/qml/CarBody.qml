import QtQuick 2.14

Item {
    id: carBody

    property int bodyType: BodyType.One
    property bool detectable: true

    signal moveEnded(var sender)

    function attachTo(item) {
        var mappedPosition = parent.mapToItem(item, x, y)

        x = mappedPosition.x
        y = mappedPosition.y
        parent = item
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

    function move(destination) {
        var duration = Math.abs(destination - x) * 10

        animation.stop()
        animation.to = destination
        animation.duration = duration
        animation.start()
    }

    function stop() {
        animation.stop()
    }

    implicitHeight: displayedImage.height
    implicitWidth: displayedImage.width

    Image {
        id: displayedImage

        source: {
            switch (bodyType) {
            case BodyType.One:
                return "qrc:/body/BodyType1.png"
            case BodyType.Two:
                return "qrc:/body/BodyType2.png"
            case BodyType.Three:
                return "qrc:/body/BodyType3.png"
            default:
                console.exception("Invalid body type:", bodyType)
            }
        }
    }

    NumberAnimation on x {
        id: animation

        onFinished: moveEnded(carBody)
    }
}
