import QtQuick 2.14
import "qrc:/common"

Item {
    id: belt

    property bool active: false

    implicitHeight: displayedAnimation.height
    implicitWidth: displayedAnimation.width

    AnimatedSprite {
        id: displayedAnimation

        running: active
        currentFrame: running ? currentFrame : 0

        frameCount: 6
        frameDuration: 500
        interpolate: false
        source: "qrc:/conveyor/Belt.png"
    }
}
