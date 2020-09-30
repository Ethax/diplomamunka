import QtQuick 2.14
import "qrc:/common"

AnimatedItem {
    id: carBody

    enum BodyType {
        TypeOne,
        TypeTwo,
        TypeThree
    }

    property int bodyType: CarBody.TypeOne

    implicitHeight: displayedImage.height
    implicitWidth: displayedImage.width

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
