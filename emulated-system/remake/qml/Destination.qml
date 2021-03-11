import QtQuick 2.14
import QtQuick.Shapes 1.14

Item {
    id: destination

    property int number: 0

    implicitHeight: displayedShape.height
    implicitWidth: displayedShape.width

    Shape {
        id: displayedShape

        height: 64
        width: 175

        ShapePath {
            fillColor: "gray"
            strokeColor: "transparent"

            PathPolyline {
                path: [
                    Qt.point(0, 0),
                    Qt.point(45, 0),
                    Qt.point(45, 8),
                    Qt.point(130, 8),
                    Qt.point(130, 0),
                    Qt.point(175, 0),
                    Qt.point(175, 64),
                    Qt.point(130, 64),
                    Qt.point(130, 56),
                    Qt.point(45, 56),
                    Qt.point(45, 64),
                    Qt.point(0, 64)
                ]
            }
        }

        Text {
            text: qsTr("C%1").arg(number)
            anchors.centerIn: parent

            color: "white"
            font {
                bold: true
                pointSize: 18
            }
        }
    }
}
