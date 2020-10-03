import QtQuick 2.14
import "qrc:/common"

Item {
    id: conveyorBelt

    property Item nextSegment: parent
    property bool running: false

    function tryPlaceOn(animatedItem) {
        if (animatedItem.overlaps(this)) {
            animatedItem.attachTo(items)
            items.register(animatedItem)
        }
    }

    function tryTakeOff(animatedItem) {
        if (animatedItem.attachedTo(hook)) {
            items.unregister(animatedItem)
            animatedItem.attachTo(scene)
        }
    }

    onRunningChanged: {
        if (running) {
            items.forEachItem(items.convey)
        } else {
            items.forEachItem(items.stop)
        }
    }

    implicitHeight: displayedImage.height
    implicitWidth: displayedImage.width

    Rectangle {
        id: displayedImage

        width: 250
        height: 75
        color: "#868686"
        border.color: "black"
    }

    Item {
        id: items

        function register(animatedItem) {
            animatedItem.destinationReached.connect(onFinished)
            animatedItem.positionChanged.connect(onPositionChanged)

            if (running) {
                convey(animatedItem)
            }
        }

        function unregister(animatedItem) {
            animatedItem.stop()
            animatedItem.destinationReached.disconnect(onFinished)
            animatedItem.positionChanged.disconnect(onPositionChanged)
        }

        function convey(animatedItem) {
            var destination = conveyorBelt.width - (animatedItem.width / 2)

            animatedItem.move(destination)
        }

        function stop(animatedItem) {//animatedItem.stop()
        }

        // connect signal: https://stackoverflow.com/a/22605752/7893951
        function onFinished(animatedItem) {
            console.log("I'm here")
            unregister(animatedItem)

            if (nextSegment instanceof ConveyorBelt_Old) {
                nextSegment.tryPlaceOn(animatedItem)
            } else {
                animatedItem.attachTo(nextSegment)
            }
        }

        function onPositionChanged(animatedItem) {//console.log("New position:", animatedItem.x)
        }

        function forEachItem(action) {
            for (var i = 0; i < children.length; ++i) {
                var child = children[i]

                if (child instanceof AnimatedItem) {
                    action(child)
                }
            }
        }

        anchors.left: displayedImage.left
        anchors.verticalCenter: displayedImage.verticalCenter
    }
}
