import QtQuick 2.5

Rectangle {
    id: root

    property SortBox sortBox: null
    readonly property bool running: internal.running
    readonly property int sortingTime: internal.milliseconds

    radius: 2.0
    gradient: Gradient {
        GradientStop { position: 0.0; color: "#CCFFCC" }
        GradientStop { position: 1.0; color: "lightgreen" }
    }
    border.width: 1
    border.color: "black"

    Text {
        anchors.centerIn: parent
        text: internal.msecondsToTime(internal.milliseconds)
    }

    QtObject {
        id: internal

        property int milliseconds: 0
        property int timeSpentPaused: 0
        property bool running
        property date startTime
        property date pauseTime

        function start() {
            running = true
            milliseconds = timeSpentPaused = 0
            startTime = new Date()
            timer.start()
        }

        function stop() {
            timer.stop()
            // Calculate the exact time from start to finish excluding the time spent paused.
            milliseconds = new Date().getTime() - startTime.getTime() - timeSpentPaused
            running = false
        }

        function msecondsToTime(msecs) {
            var minutes = Math.floor(msecs / (1000 * 60));
            var seconds = Math.floor((msecs / 1000) % 60);
            var mseconds = Math.ceil(msecs % 1000);

            if (minutes < 10) minutes = "0" + minutes
            if (seconds < 10) seconds = "0" + seconds
            if (mseconds < 100) {
                if (mseconds < 10)
                    mseconds = "00" + mseconds
                else
                    mseconds = "0" + mseconds
            }

            return minutes + ":" + seconds + ":" + mseconds
        }
    }

    states: [
        State {
            name: "idle"
            when: !sortBox.sorting
        },
        State {
            name: "running"
            when: sortBox.sorting
        }
    ]

    transitions: [
        Transition {
            from: "idle"; to: "running"
            ScriptAction { script: internal.start() }
        },
        Transition {
            from: "running"; to: "idle"
            ScriptAction { script: internal.stop() }
        }
    ]

    Timer {
        id: timer
        interval: 100; repeat: true
        onTriggered: internal.milliseconds += interval
    }
}
