#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "serialport.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<SerialPort>("com.wiseelement.qmlcomponents", 1, 0, "SerialPort");

    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.load(QUrl(QStringLiteral("qrc:/camera_test_plane.qml")));

    return app.exec();
}
