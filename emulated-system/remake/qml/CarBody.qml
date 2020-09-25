import QtQuick 2.14

Item {
    id: carBody

    enum BodyType {
        TypeOne,
        TypeTwo,
        TypeThree
    }

    property int bodyType: CarBody.TypeOne
    property int timeUnit: 10

    implicitHeight: displayedImage.height
    implicitWidth: displayedImage.width

    function attachTo(item) {
        var newPoint = parent.mapToItem(item, x, y)

        parent = item
        x = newPoint.x
        y = newPoint.y
    }

    function overlaps(item) {
        var thisRect = mapToItem(null, 0, 0, width, height)
        var otherRect = item.mapToItem(null, 0, 0, item.width, item.height)

        return thisRect.x < otherRect.x + otherRect.width
                && otherRect.x < thisRect.x + thisRect.width
                && thisRect.y < otherRect.y + otherRect.height
                && otherRect.y < thisRect.y + thisRect.height
    }

    function animate(destination) {
        var duration = Math.abs(destination - x) * timeUnit

        animation.stop()
        animation.to = destination
        animation.duration = duration
        animation.start()
    }

    function stop() {
        animation.stop()
    }

    NumberAnimation on x {
        id: animation
    }

    Image {
        id: displayedImage

        source: {
            switch (bodyType) {
            case CarBody.TypeOne:
                return "BodyType1.png"
            case CarBody.TypeTwo:
                return "BodyType2.png"
            case CarBody.TypeThree:
                return "BodyType3.png"
            default:
                console.exception("Invalid body type:", bodyType)
            }
        }
    }
}
