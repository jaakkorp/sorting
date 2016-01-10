#TEMPLATE = lib

#TARGET = qmlsortboxmodelplugin
#TARGETPATH = Qt/labs/sortboxmodel

#CONFIG += qt plugin
#QT += qml quick

#HEADERS += sortboxmodel.h \
#           sortenginethread.h \
#           sortengine.h \
#           sortengine_p.h \
#           raceresults.h \
#           readysteadygo.h \
#           constants.h


#SOURCES += sortboxmodel.cpp \
#           sortenginethread.cpp \
#           sortengine.cpp \
#           sortengine_p.cpp \
#           raceresults.cpp \
#           readysteadygo.cpp \
#           plugin.cpp


#QTDIR_build:DESTDIR = $$QT_BUILD_TREE/imports/$$TARGETPATH
#target.path = $$[QT_INSTALL_IMPORTS]/$$TARGETPATH

#qmldir.files += $$PWD/qmldir
#qmldir.path +=  $$[QT_INSTALL_IMPORTS]/$$TARGETPATH

#INSTALLS += target qmldir

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

DESTPATH=$$[QML2_IMPORT_PATH]/Qt/labs/sortboxmodel

target.path=$$DESTPATH
qmldir.files=$$PWD/qmldir
qmldir.path=$$DESTPATH
INSTALLS += target qmldir

OTHER_FILES += qmldir

# Copy the qmldir file to the same folder as the plugin binary
QMAKE_POST_LINK += $$QMAKE_COPY $$replace($$list($$quote($$PWD/qmldir) $$DESTDIR), /, $$QMAKE_DIR_SEP)
