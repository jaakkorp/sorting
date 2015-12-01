import QtQuick 2.5

Rectangle  {
    id: root

    signal clicked

    property bool enabled: true

    radius: 2
    gradient: Gradient {
        GradientStop { id: gradientStart; position: 0.0; color: "red" }
        GradientStop { id: gradientEnd; position: 1.0; color: "#B0171F" }
    }
    border.color: "black"

    Text {
        anchors.centerIn: parent
        text: "x"
        color: "white"
        font.bold: true
        style: Text.Outline
        styleColor: "black"
    }

    MouseArea {
        id: mouseArea

        property bool hoveringOver

        anchors.fill: parent
        enabled: root.enabled
        hoverEnabled: true
        onEntered: hoveringOver = true
        onExited: hoveringOver = false
        onClicked: root.clicked()
    }

    states: [
        State {
            name: "pressed"
            when: mouseArea.pressed
            PropertyChanges { target: gradientStart; color: "#993300" }
            PropertyChanges { target: gradientEnd; color: "#B0171F" }
        },
        State {
            name: "active"
            when: mouseArea.hoveringOver
        },
        State {
            name: "enabled"
            when: enabled
            PropertyChanges { target: root; opacity: 0.7 }
        },
        State {
            name: "disabled"
            when: !enabled
            PropertyChanges { target: root; opacity: 0.4 }
        }
    ]
}
