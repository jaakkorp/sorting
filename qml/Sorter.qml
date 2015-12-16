import QtQuick 2.5
import Qt.labs.sortboxmodel 1.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2

Item {
    id: root

    signal closed

    property int barCount
    property alias selected: checkBox.checked
    property int result
    readonly property alias sortingAlgorithm: comboBox.currentIndex
    property alias animationDuration: sortBox.animationDuration
    readonly property bool sorting: sortBox.sorting
    readonly property bool aboutToSort: readySteadyGo.running
    readonly property bool sorted: sortBox.sorted && !sortingDuration.running
    readonly property int sortingTime: sortingDuration.sortingTime
    readonly property bool needResult: internal.needResult

    onResultChanged: {
        if (result !== 0)
            resultFlash.showResult(result)
    }

    onSortingChanged: {
        if (sorting)
            resultFlash.clear()
    }

    onSortedChanged: {
        if (!sorted)
            resultFlash.clear()
    }

    function setSortingAlgorithm(sortingAlgorithm) {
        if (!sorting)
            comboBox.currentIndex = sortingAlgorithm
    }

    function sort(initTime) {
        var willSort = false

        if (selected && !sorted && !sorting) {
            internal.needResult = true
            root.result = 0;
            readySteadyGo.countDown(initTime)
            willSort = true
        }

        return willSort
    }

    function scramble() {
        sortBox.scramble();
    }

    function setOrder(array) {
        sortBox.setOrder(array)
    }

    function setSortedFalse() {
        sortBox.setSortedFalse()
    }

    ColumnLayout {
        id: column
        spacing: 10
        anchors.fill: parent

        RowLayout {
            Layout.fillWidth: true

            ComboBox {
                id: comboBox
                Layout.minimumWidth: root.width / 2
                Layout.minimumHeight: comboBox.implicitHeight
                currentIndex: root.sortingAlgorithm
                onCurrentIndexChanged: setSortingAlgorithm(currentIndex)
                enabled: !sortBox.sorting && !readySteadyGo.running
                model: sortBox.algorithms()
            }

            Item {
                Layout.fillWidth: true
            }

            CloseButton {
                id: closeButton
                Layout.preferredWidth: height
                Layout.preferredHeight: comboBox.height
                Layout.alignment: Qt.AlignLeft
                enabled: !sortBox.sorting
                onClicked: root.closed()
            }
        }

        SortBox {
            id: sortBox
            Layout.fillWidth: true
            Layout.fillHeight: true
            barCount: root.barCount
            sortingAlgorithm: comboBox.currentIndex

            ResultFlash {
                id: resultFlash
            }

            ReadySteadyGoLights {
                id: readySteadyGoLights
            }
        }

        RowLayout {

            spacing: 10
            /*add: Transition {
                    NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 500 }
                    NumberAnimation { property: "scale"; from: 0; to: 1.0; easing.type: Easing.OutCirc; duration: 500 }
                }
                move: Transition {
                    NumberAnimation { property: "x"; easing.type: Easing.OutCirc; duration: 500 }
                    NumberAnimation { property: "y"; easing.type: Easing.OutCirc; duration: 500 }
                }*/

            Button {
                text: "Sort"
                enabled: !sortBox.sorting && !sortBox.sorted && !readySteadyGo.running
                onClicked: {
                    internal.needResult = false
                    root.result = 0
                    sortBox.sort()
                }
            }

            Button {
                text: "Set unsorted"
                visible: !sortBox.sorting && !readySteadyGo.running && sortBox.sorted
                onClicked: {
                    sortBox.setSortedFalse()
                }
            }

            Button {
                text: "Scramble"
                enabled: !sortBox.sorting && !readySteadyGo.running
                onClicked: sortBox.scramble()
            }

            SortingDuration {
                id: sortingDuration
                Layout.preferredHeight: parent.height
                Layout.preferredWidth: Layout.preferredHeight * 5
                sortBox: sortBox
            }

            Item {
                Layout.fillWidth: true
            }

            CheckBox {
                id: checkBox
                enabled: !sortBox.sorting && !readySteadyGo.running
            }
        }
    }

    ReadySteadyGo {
        id: readySteadyGo

        onInit: readySteadyGoLights.init()
        onReady: readySteadyGoLights.ready()
        onSteady: readySteadyGoLights.steady()
        onGo: {
            readySteadyGoLights.go()
            sortBox.sort()
        }
    }

    QtObject {
        id: internal
        property bool needResult
    }
}
