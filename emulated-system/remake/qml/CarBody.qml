import QtQuick 2.14

Item {
    enum BodyType {
        TypeOne,
        TypeTwo,
        TypeThree
    }

    property int bodyType: CarBody.TypeOne

    implicitHeight: carBody.height
    implicitWidth: carBody.width

    onBodyTypeChanged: {
        switch (bodyType) {
        case CarBody.TypeOne:
            carBody.source = "BodyType1.png"
            break
        case CarBody.TypeTwo:
            carBody.source = "BodyType2.png"
            break
        case CarBody.TypeThree:
            carBody.source = "BodyType3.png"
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

    Image {
        id: carBody

        source: "BodyType1.png"
    }
}
