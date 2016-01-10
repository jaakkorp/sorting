TEMPLATE = lib
CONFIG += plugin c++14
QT += qml quick

DESTDIR = ../sortboxmodel
TARGET = $$qtLibraryTarget(qmlsortboxmodelplugin)

HEADERS += sortboxmodel.h \
           sortengine.h \
           sortengineworker.h \
           sortingalgorithm.h \
           raceresults.h \
           readysteadygo.h \
           constants.h \
           algorithms/bubblesort.h \
           algorithms/exchangesort.h \
           algorithms/insertionsort.h \
           algorithms/mergesort.h \
           algorithms/selectionsort.h \
           algorithms/shellsort.h \
           algorithms/quicksort.h

SOURCES += sortboxmodel.cpp \
           sortengine.cpp \
           sortengineworker.cpp \
           sortingalgorithm.cpp \
           raceresults.cpp \
           readysteadygo.cpp \
           plugin.cpp \
           algorithms/bubblesort.cpp \
           algorithms/exchangesort.cpp \
           algorithms/insertionsort.cpp \
           algorithms/mergesort.cpp \
           algorithms/selectionsort.cpp \
           algorithms/shellsort.cpp \
           algorithms/quicksort.cpp

DESTPATH=$$[QT_INSTALL_QML]/Qt/labs/sortboxmodel

target.path=$$DESTPATH
qmldir.files=$$PWD/qmldir
qmldir.path=$$DESTPATH
INSTALLS += target qmldir

OTHER_FILES += qmldir

# Copy the qmldir file to the same folder as the plugin binary
QMAKE_POST_LINK += $$QMAKE_COPY $$replace($$list($$quote($$PWD/qmldir) $$DESTDIR), /, $$QMAKE_DIR_SEP)
