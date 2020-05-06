import QtQuick 2.14

Image {
    enum BodyType {
        TypeOne,
        TypeTwo,
        TypeThree
    }

    property int bodyType: CarBody.TypeOne

    function attachTo(item) {
        var newPoint = parent.mapToItem(item, x, y)

        parent = item
        x = newPoint.x
        y = newPoint.y
        z = 0
    }

    source: "BodyType1.png"
    onBodyTypeChanged: {
        switch (bodyType) {
        case CarBody.TypeOne:
            source = "BodyType1.png"
            break
        case CarBody.TypeTwo:
            source = "BodyType2.png"
            break
        case CarBody.TypeThree:
            source = "BodyType3.png"
            break
        default:
            console.exception("Invalid body type:", bodyType)
        }
    }
}
