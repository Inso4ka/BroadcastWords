TEMPLATE = app
TARGET = Broadcast-words
CONFIG += c++17
QT += widgets
QT += core gui network


SOURCES += UI/main.cpp \
    UI/mainwindow.cpp

FORMS += \
    UI/mainwindow.ui

HEADERS += \
    UI/mainwindow.h

RESOURCES += \
    Resources/qrc.qrc
