import QtQuick 2.14
import QtQuick.Controls 2.14

Item {
    id: carBodyInserter

    property int bodyType: BodyType.One

    signal destinationSelected(var destination)

    implicitHeight: displayedButton.height
    implicitWidth: displayedButton.width

    Button {
        id: displayedButton

        display: AbstractButton.TextUnderIcon
        palette.button: "#dde1e4"

        text: {
            switch (bodyType) {
            case BodyType.One:
                return qsTr("Típus 1")
            case BodyType.Two:
                return qsTr("Típus 2")
            case BodyType.Three:
                return qsTr("Típus 3")
            default:
                throw "Invalid body type: " + bodyType
            }
        }

        icon {
            height: 24
            width: 52

            source: {
                switch (bodyType) {
                case BodyType.One:
                    return "qrc:/body/BodyType1.png"
                case BodyType.Two:
                    return "qrc:/body/BodyType2.png"
                case BodyType.Three:
                    return "qrc:/body/BodyType3.png"
                default:
                    throw "Invalid body type: " + bodyType
                }
            }
        }

        onClicked: destinationMenu.open()

        Menu {
            id: destinationMenu

            x: 0
            y: displayedButton.height

            MenuItem {
                text: qsTr("Cella 1")
                onTriggered: destinationSelected(0)
            }

            MenuItem {
                text: qsTr("Cella 2")
                onTriggered: destinationSelected(1)
            }

            MenuItem {
                text: qsTr("Cella 3")
                onTriggered: destinationSelected(2)
            }
        }
    }
}
