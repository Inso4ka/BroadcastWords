TEMPLATE = app
TARGET = Broadcast-words
CONFIG += c++17
QT += widgets
QT += core gui network


SOURCES += UI/main.cpp \
    UI/mainwindow.cpp \
    UI/broadcast.cpp

FORMS += \
    UI/mainwindow.ui \
    UI/broadcast.ui

HEADERS += \
    UI/mainwindow.h \
    UI/broadcast.h

RESOURCES += \
    Resources/qrc.qrc
