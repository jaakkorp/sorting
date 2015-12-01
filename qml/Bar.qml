import QtQuick 2.5

Rectangle {
    id: root
    property int animationDuration
    property alias moving: animation.running

    color: "white"
    border.color: "black"
    border.width: 1

    Behavior on height {
        NumberAnimation {
            id: animation
            duration: root.animationDuration
            easing.type: Easing.OutExpo
        }
    }
}

