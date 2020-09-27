import QtQuick 2.14

Image {
    property int orientation: Orientation.Upward

    Binding on rotation {
        when: orientation === Orientation.Downward
        value: 180
    }

    Binding on rotation {
        when: orientation === Orientation.Upward
        value: 0
    }
}
