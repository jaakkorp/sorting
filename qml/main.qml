import QtQuick 2.5
import Qt.labs.sortingmodel 1.0
import QtQuick.Controls 1.4
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2

ApplicationWindow {
    id: root

    Component.onCompleted: visibility = Window.Maximized

    ColumnLayout {
        id: column

        anchors.centerIn: parent
        spacing: 30

        Grid {
            id: grid

            Layout.alignment: Qt.AlignHCenter

            columns: Math.ceil(Math.sqrt(sorterModel.count))
            rows: Math.ceil(Math.sqrt(sorterModel.count))
            spacing: 30
            property int itemHeight: 324
            property int itemWidth: 576

            add: Transition {
                NumberAnimation { property: "opacity"; from: 0; to: 1.0; duration: 500 }
                NumberAnimation { property: "scale"; from: 0; to: 1.0; easing.type: Easing.OutCirc; duration: 500 }
            }
            move: Transition {
                NumberAnimation { property: "x"; easing.type: Easing.OutCirc; duration: 500 }
                NumberAnimation { property: "y"; easing.type: Easing.OutCirc; duration: 500 }
            }

            Repeater {
                model: sorterModel

                Sorter {
                    height: grid.itemHeight
                    width: grid.itemWidth
                    barCount: count
                    onSortedChanged: if (sorted && needResult) {
                                         result = results.getResult()
                                         internal.sorted(sortingTime)
                                     }
                    onClosed: internal.deleteSorter(index)

                    Component.onCompleted: {
                        setSortingAlgorithm(algorithm)

                        selectAll.clicked.connect(function() {
                            selected = true
                        })

                        deselectAll.clicked.connect(function() {
                            selected = false
                        })

                        scrambleOrder.clicked.connect(function() {
                            if (selected)
                                scramble()
                        })

                        setUnsorted.clicked.connect(function() {
                            if (selected)
                                setSortedFalse()
                        })

                        internal.race.connect(function() {
                            if (sort(internal.initTime)) {
                                internal.sortingItemsCount++
                                internal.racing = true
                            }
                        })

                        comboBox.currentIndexChanged.connect(function() {
                            if (selected)
                                setSortingAlgorithm(comboBox.currentIndex)
                        })

                        internal.raceFinished.connect(function() {
                            if (selected && sorted && needResult) {
                                result = results.getResult(sortingTime)
                            }
                        })

                        internal.randomOrderRequested.connect(function() {
                            if (selected) {
                                setOrder(internal.randomOrder)
                            }
                        })

                        internal.reverseOrderRequested.connect(function() {
                            if (selected) {
                                setOrder(internal.reverseOrder)
                            }
                        })
                    }
                }
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignHCenter
            spacing: 20

            Button {
                id: selectAll

                text: "Select all"
                enabled: !internal.racing
            }

            Button {
                id: deselectAll

                text: "Deselect all"
                enabled: !internal.racing
            }

            Button {
                text: "Sort"
                enabled: !internal.racing
                onClicked: internal.sortSelected()
            }

            Button {
                id: scrambleOrder

                text: "Scramble"
                enabled: !internal.racing
            }

            Button {
                text: "Set reverse order"
                enabled: !internal.racing
                onClicked: internal.setReverseOrder()
            }

            Button {
                text: "Set same order"
                enabled: !internal.racing
                onClicked: internal.setRandomOrder()
            }

            Button {
                id: setUnsorted

                text: "Set sorted unsorted"
                enabled: !internal.racing
                onClicked: internal.setSortedFalse()
            }

            Button {
                text: "Add sorter"
                enabled: sorterModel.count < 6
                onClicked: internal.addSorter()
            }

            ComboBox {
                id: comboBox

                Layout.minimumWidth: 150
                enabled: !internal.racing
                model: sortBoxModel.algorithms()
            }
        }
    }

    ListModel {
        id: sorterModel

        ListElement {
            count: 100
            algorithm: SortBoxModel.QuickSort
        }

        ListElement {
            count: 100
            algorithm: SortBoxModel.QuickSort
        }

        ListElement {
            count: 100
            algorithm: SortBoxModel.QuickSort
        }

        ListElement {
            count: 100
            algorithm: SortBoxModel.QuickSort
        }

        ListElement {
            count: 100
            algorithm: SortBoxModel.QuickSort
        }

        ListElement {
            count: 100
            algorithm: SortBoxModel.QuickSort
        }
    }

    SortBoxModel {
        id: sortBoxModel
    }

    RaceResults {
        id: results
    }

    ReadySteadyGo {
        id: readySteadyGo
    }

    QtObject {
        id: internal

        property bool racing
        property int sortingItemsCount
        property int sortedItemsCount
        property var initTime
        property var randomOrder
        property var reverseOrder

        signal race
        signal raceFinished
        signal randomOrderRequested
        signal reverseOrderRequested

        function sortSelected() {
            reset()
            initTime = readySteadyGo.initTime()
            race()
        }

        function sorted(sortingTime) {
            sortedItemsCount++
            results.addRaceTime(sortingTime)

            if (sortedItemsCount === sortingItemsCount) {
                racing = false
                raceFinished()
            }
        }

        function setReverseOrder() {
            reverseOrder = sortBoxModel.reverseOrder(100)
            reverseOrderRequested()
        }

        function setRandomOrder() {
            randomOrder = sortBoxModel.randomOrder(100)
            randomOrderRequested()
        }

        function addSorter() {
            if (sorterModel.count < 6)
                sorterModel.insert(sorterModel.count, {"count": 100, "algorithm": SortBoxModel.QuickSort});
        }

        function deleteSorter(index) {
            if (sorterModel.count > 1) {
                sortingItemsCount--
                sorterModel.remove(index, 1)
            }
        }

        function reset() {
            sortingItemsCount = sortedItemsCount = 0
            results.reset()
        }
    }
}
