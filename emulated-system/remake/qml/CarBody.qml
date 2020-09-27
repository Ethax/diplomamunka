import QtQuick 2.14
import "qrc:/common"

AttachableItem {
    id: carBody

    enum BodyType {
        TypeOne,
        TypeTwo,
        TypeThree
    }

    property int bodyType: CarBody.TypeOne

    implicitHeight: displayedImage.height
    implicitWidth: displayedImage.width

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
