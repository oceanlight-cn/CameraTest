TEMPLATE = app

QT += qml quick serialport
CONFIG += c++11

SOURCES += main.cpp \
    serialport.cpp \
    CustomIO/ICustomIO.cpp \
    CustomIO/NetIO.cpp \
    CustomIO/SerialPortIO.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH += $$PWD

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    serialport.h \
    CustomIO/ICustomIO.h \
    CustomIO/NetIO.h \
    CustomIO/SerialPortIO.h \
    globaldef.h

INCLUDEPATH += $$PWD/..
