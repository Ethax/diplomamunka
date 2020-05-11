import QtQuick 2.14

Item {
    id: carBody

    enum BodyType {
        TypeOne,
        TypeTwo,
        TypeThree
    }

    property int bodyType: CarBody.TypeOne

    implicitHeight: displayedImage.height
    implicitWidth: displayedImage.width

    onBodyTypeChanged: {
        switch (bodyType) {
        case CarBody.TypeOne:
            displayedImage.source = "BodyType1.png"
            break
        case CarBody.TypeTwo:
            displayedImage.source = "BodyType2.png"
            break
        case CarBody.TypeThree:
            displayedImage.source = "BodyType3.png"
            break
        default:
            console.exception("Invalid body type:", bodyType)
        }
    }

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

    Image {
        id: displayedImage
        source: "BodyType1.png"
    }
}
