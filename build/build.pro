TEMPLATE = app

# Will build the final executable in the main project directory.
TARGET = ../sorting

CONFIG += qt c++14
QT += quick #widgets

SOURCES += main.cpp

RESOURCES += \
    ../resources.qrc

target.path = .
INSTALLS += target

#LIBS += -L../model lmodel


