import QtQuick 2.14

Image {
    source: "RunwayBeam.png"
    property alias bridgePosition: bridge.y

    Image {
        property real stepSize: parent.height / 3.0

        id: bridge

        anchors.rightMargin: -17
        anchors.right: parent.right
        source: "Bridge.png"

        Behavior on y {
            id: transition
            property int distance: Math.abs(bridge.y - targetValue)

            NumberAnimation {
                duration: 6000 // * Math.ceil(Math.abs(                                               to - from) / bridge.stepSize)
                onRunningChanged: {
                    if (running) {
                        console.log("Target value: ", transition.targetValue)
                        console.log("Current value: ", bridge.y)
                        console.log("Distance: ", transition.distance)
                        console.log("Step size: ", bridge.stepSize)
                        console.log("-----------------------------------")
                    }
                }
                easing.type: Easing.InOutCubic
            }
        }
    }
} //Image {//    property int clampDistance: 18//    id: trolley//    source: "Trolley.png"//    Image {//        id: rightClamp//        y: -trolley.clampDistance//        z: -1//        anchors.horizontalCenter: parent.horizontalCenter//        source: "RightClamp.png"//        Behavior on y {//            NumberAnimation {//                duration: 2000//            }//        }//    }//    Image {//        id: rightFork//        scale: 1//        z: -3//        anchors {//            top: rightClamp.top//            horizontalCenter: parent.horizontalCenter//        }//        source: "RightFork.png"//    }//    Image {//        id: leftClamp//        y: trolley.clampDistance//        z: -1//        source: "LeftClamp.png"//        anchors.horizontalCenter: parent.horizontalCenter//        Behavior on y {//            NumberAnimation {//                duration: 2000//            }//        }//    }//    Image {//        id: leftFork//        z: -3//        source: "LeftFork.png"//        anchors {//            bottom: leftClamp.bottom//            horizontalCenter: parent.horizontalCenter//        }//    }//}

/*##^##
Designer {
    D{i:0;formeditorZoom:6}
}
##^##*/

