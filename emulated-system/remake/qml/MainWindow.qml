import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14

Window {
    id: mainWindow
    visible: true
    width: 800
    height: 600

    Rectangle {
        id: master
        x: 10
        y: 10
        width: 50
        height: 50
        color: "#00ff00"

        Behavior on x {
            NumberAnimation {
                duration: 6000
                easing.type: Easing.InOutCubic

                onRunningChanged: {
                    if (!running) {
                        master.color = "#ff0000"
                    }
                }
            }
        }

        onXChanged: {
            if (carBody.overlaps(sensor)) {
                sensor.color = "#ff0000"
            } else {
                sensor.color = "#ffff00"
            }
        }
    }

    Button {
        id: move
        x: 50
        y: 327
        text: qsTr("Move")

        onClicked: {
            master.x = 400
        }
    }

    //    CheckBox {
    //        id: attach
    //        x: 300
    //        y: 300
    //        text: qsTr("Attach")

    //        onClicked: {
    //            if (checked) {
    //                carBody.attachTo(master)
    //            } else {
    //                carBody.attachTo(mainWindow.contentItem)
    //            }
    //        }
    //    }
    Crane {
        id: crane
        x: 563
        y: 54
    }

    CarBody {
        id: carBody
        bodyType: CarBody.TypeOne
        x: 82
        y: 123

        Component.onCompleted: {
            attachTo(master)
        }
    }

    Button {
        x: 676
        y: 507
        text: qsTr("Move crane")

        onClicked: {
            crane.position++
        }
    }

    Button {
        x: 536
        y: 507
        text: qsTr("Open/Close")

        onClicked: {
            crane.open ^= 1
        }
    }

    Rectangle {
        id: sensor
        x: 257
        y: 81
        width: 5
        height: 200
        color: "#ffff00"
    }
}
