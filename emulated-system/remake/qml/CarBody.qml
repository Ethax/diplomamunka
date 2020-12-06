import QtQuick 2.14
import "qrc:/common"

AnimatedItem {
    id: carBody

    property int bodyType: BodyType.One

    implicitHeight: displayedImage.height
    implicitWidth: displayedImage.width

    Image {
        id: displayedImage

        source: {
            switch (bodyType) {
            case BodyType.One:
                return "BodyType1.png"
            case BodyType.Two:
                return "BodyType2.png"
            case BodyType.Three:
                return "BodyType3.png"
            default:
                console.exception("Invalid body type:", bodyType)
            }
        }
    }
}
