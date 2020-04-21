#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "serialport.h"
#include "CameraTest.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<SerialPort>("com.wiseelement.qmlcomponents", 1, 0, "SerialPort");
    qmlRegisterType<CameraTest>("com.wiseelement.qmlcameratest", 1, 0, "CameraTest");

    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.load(QUrl(QStringLiteral("qrc:/camera_test_plane.qml")));

    return app.exec();
}
