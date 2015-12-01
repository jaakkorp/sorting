import QtQuick 2.5
import Qt.labs.sortboxmodel 1.0
import QtQuick.Controls 1.4

Rectangle {
    id: root

    signal closed

    property int barCount
    property alias selected: checkBox.checked
    property int result
    property alias sortingAlgorithm: comboBox.currentIndex
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

    QtObject {
        id: internal
        property bool needResult
    }

    Column {
        id: column
        spacing: 10
        anchors.margins: 5

        Row {
            width: sortBox.width
            spacing: width - comboBox.width - closeButton.width

            ComboBox {
                id: comboBox
                width: root.width / 2
                currentIndex: root.sortingAlgorithm
                onCurrentIndexChanged: root.sortingAlgorithm = currentIndex
                enabled: !sortBox.sorting && !readySteadyGo.running
                model: ListModel {
                    ListElement { text: "Bubble sort"; }
                    ListElement { text: "Exchange sort"; }
                    ListElement { text: "Selection sort"; }
                    ListElement { text: "Insertion sort"; }
                    ListElement { text: "Shell sort"; }
                    ListElement { text: "Merge sort"; }
                    ListElement { text: "Quick sort"; }
                }
            }

            CloseButton {
                id: closeButton
                height: comboBox.height
                width: height
                enabled: !sortBox.sorting
                onClicked: root.closed()
            }
        }

        SortBox {
            id: sortBox
            height: root.height * 0.8; width: root.width
            barCount: root.barCount
            sortingAlgorithm: comboBox.currentIndex

            ResultFlash {
                id: resultFlash
            }

            ReadySteadyGoLights {
                id: readySteadyGoLights
            }
        }

        Rectangle {
            width: sortBox.width
            color: root.color

            Component.onCompleted: height = childrenRect.height

            Row {
                id: row
                spacing: 10
                add: Transition {
                    NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 500 }
                    NumberAnimation { property: "scale"; from: 0; to: 1.0; easing.type: Easing.OutCirc; duration: 500 }
                }
                move: Transition {
                    NumberAnimation { property: "x"; easing.type: Easing.OutCirc; duration: 500 }
                    NumberAnimation { property: "y"; easing.type: Easing.OutCirc; duration: 500 }
                }

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
                    height: root.height * 0.1 - column.spacing; width: height * 5
                    sortBox: sortBox
                }

                Label {
                    id: operationCountLabel
                    text: sortBox.operationCount
                }

                Label {
                    id: resultLabel
                    text: result === 0 ? "" : result
                }

                CheckBox {
                    id: checkBox
                    enabled: !sortBox.sorting && !readySteadyGo.running
                }
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

    function sort(initTime) {
        if (!sortBox.sorted) {
            internal.needResult = true
            root.result = 0;
            readySteadyGo.countDown(initTime)
        }
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
}
