TEMPLATE = app
TARGET = Broadcast-words
CONFIG += c++17
QT += widgets
QT += network



SOURCES += UI/main.cpp \
    UI/mainwindow.cpp \
    UI/broadcast.cpp \
    Network/servercommunication.cpp

FORMS += \
    UI/mainwindow.ui \
    UI/broadcast.ui

HEADERS += \
    UI/mainwindow.h \
    UI/broadcast.h \
    Network/servercommunication.h

RESOURCES += \
    Resources/qrc.qrc
