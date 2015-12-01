TEMPLATE = subdirs
SUBDIRS = build model

# build must be last:
#CONFIG += ordered
#SUBDIRS += build

OTHER_FILES += \
    qml/Bar.qml \
    qml/main.qml \
    qml/Sorter.qml \
    qml/SortBox.qml \
    qml/CloseButton.qml \
    qml/SortingDuration.qml \
    qml/ResultFlash.qml \
    qml/ReadySteadyGoLights.qml

RESOURCES += \
    resources.qrc
