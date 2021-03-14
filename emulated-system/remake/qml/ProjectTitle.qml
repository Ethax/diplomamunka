import QtQuick 2.14

Column {
    id: projectTitle

    property string title: ""
    property string author: ""

    padding: 10
    spacing: 5

    Text {
        text: title

        font {
            bold: true
            pointSize: 16
        }
    }

    Text {
        text: qsTr("Készítette: %1").arg(author)
    }
}
