#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QQuickItem>

class SerialPort : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(SerialPort)
//    Q_PROPERTY(QStringList PortName READ getcoms NOTIFY ComChanged)

public:
    SerialPort(QQuickItem *parent = 0);
    ~SerialPort();

    Q_INVOKABLE void loadcoms();
    Q_INVOKABLE QStringList getcoms();

    void fLoadComs();

private:
    QStringList m_coms;

signals:
    void comChanged();
};

#endif // SERIALPORT_H
