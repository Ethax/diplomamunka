import QtQuick 2.14
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4

Item {
    id: operation

    readonly property int selection: {
        switch (selector.value) {
        case 0:
            return Operation.Observation
        case 1:
            return Operation.Inspection
        case 2:
            return Operation.Correction
        default:
            throw "Invalid operation value: " + value
        }
    }

    implicitHeight: selector.height
    implicitWidth: selector.width

    Dial {
        id: selector

        minimumValue: 0
        maximumValue: 2
        stepSize: 1

        height: width
        width: 85
        tickmarksVisible: true

        style: DialStyle {
            labelInset: -10

            tickmarkLabel: Text {
                color: "#515151"
                styleColor: "#ffffff"
                style: Text.Raised

                text: {
                    switch (styleData.value) {
                    case 0:
                        return qsTr("Figyel")
                    case 1:
                        return qsTr("Vizsgál")
                    case 2:
                        return qsTr("Javít")
                    default:
                        throw "Invalid operation value: " + styleData.value
                    }
                }
            }
        }
    }
}
