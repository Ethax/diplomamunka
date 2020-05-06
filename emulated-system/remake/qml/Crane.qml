import QtQuick 2.14

Image {
    id: runwayBeam

    property int position: 0

    source: "RunwayBeam.png"
    onPositionChanged: {
        switch (position) {
        case 1:
            bridge.y = 2 * bridge.stepSize
            break
        case 3:
            bridge.y = bridge.stepSize
            break
        case 5:
            bridge.y = 0
            break
        case 7:
            bridge.y = 3 * bridge.stepSize
            break
        default:
            console.exception("Invalid position:", position)
        }
    }

    Image {
        id: bridge

        property real stepSize: (runwayBeam.height - height) / 3.0

        anchors.rightMargin: -17
        anchors.right: parent.right
        source: "Bridge.png"
        y: 2 * bridge.stepSize

        Behavior on y {
            id: bridgeMotion

            NumberAnimation {
                easing.type: Easing.InOutCubic
                duration: {
                    var distance = Math.abs(bridge.y - bridgeMotion.targetValue)
                    var numberOfSteps = Math.round(distance / bridge.stepSize)

                    return 6000 * numberOfSteps
                }
            }
        }
    }
} //Image {//    property int clampDistance: 18//    id: trolley//    source: "Trolley.png"//    Image {//        id: rightClamp//        y: -trolley.clampDistance//        z: -1//        anchors.horizontalCenter: parent.horizontalCenter//        source: "RightClamp.png"//        Behavior on y {//            NumberAnimation {//                duration: 2000//            }//        }//    }//    Image {//        id: rightFork//        scale: 1//        z: -3//        anchors {//            top: rightClamp.top//            horizontalCenter: parent.horizontalCenter//        }//        source: "RightFork.png"//    }//    Image {//        id: leftClamp//        y: trolley.clampDistance//        z: -1//        source: "LeftClamp.png"//        anchors.horizontalCenter: parent.horizontalCenter//        Behavior on y {//            NumberAnimation {//                duration: 2000//            }//        }//    }//    Image {//        id: leftFork//        z: -3//        source: "LeftFork.png"//        anchors {//            bottom: leftClamp.bottom//            horizontalCenter: parent.horizontalCenter//        }//    }//}
