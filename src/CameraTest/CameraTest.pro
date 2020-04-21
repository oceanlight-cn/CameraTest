TEMPLATE = app

QT += qml quick serialport
CONFIG += c++11

SOURCES +=  \
    serialport.cpp \
    CustomIO/ICustomIO.cpp \
    CustomIO/NetIO.cpp \
    CustomIO/SerialPortIO.cpp \
    CustomIO/DataSource.cpp \
    CustomIO/DataSourceManager.cpp \
    CustomIO/IOFactory.cpp \
    CustomIO/TriggerSource.cpp \
    CustomIO/TriggerSourceManager.cpp \
    Helper/EnumTypeConverter.cpp \
    Queue/ReadParser.cpp \
    Queue/ReadQueueThread.cpp \
    TestModule/ReadImageModule.cpp \
    TestModule/CustomIoReadProcessor.cpp \
    TestModule/TestProcessManager.cpp \
    CameraTest.cpp \
    main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH += $$PWD

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    globaldef.h \
    serialport.h \
    CustomIO/ICustomIO.h \
    CustomIO/NetIO.h \
    CustomIO/SerialPortIO.h \
    CustomIO/DataSource.h \
    CustomIO/DataSourceManager.h \
    CustomIO/IOFactory.h \
    CustomIO/TriggerSource.h \
    CustomIO/TriggerSourceManager.h \
    Helper/EnumTypeConverter.h \
    Helper/LaterTimer.hpp \
    Queue/ReadParser.h \
    Queue/ReadQueue.h \
    Queue/ReadQueueThread.h \
    TestModule/ReadImageModule.h \
    TestModule/CustomIoReadProcessor.h \
    TestModule/TestProcessManager.h \
    CameraTest.h

INCLUDEPATH += $$PWD/..
