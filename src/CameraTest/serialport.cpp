#include "serialport.h"
#include <QSerialPortInfo>
#include <QSerialPort>
#include <thread>

using namespace std;

SerialPort::SerialPort(QQuickItem *parent):
    QQuickItem(parent)
{
    // By default, QQuickItem does not draw anything. If you subclass
    // QQuickItem to create a visual item, you will need to uncomment the
    // following line and re-implement updatePaintNode()

    // setFlag(ItemHasContents, true);
}

SerialPort::~SerialPort()
{
}

void SerialPort::loadcoms()
{
    std::thread t1(std::bind(&SerialPort::fLoadComs, this));
    t1.detach();
}

QStringList SerialPort::getcoms()
{
    return m_coms;
}

void SerialPort::fLoadComs()
{
    QStringList lstComs;
    QList<QSerialPortInfo> PortInfolist =  QSerialPortInfo::availablePorts();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        lstComs.append(info.portName());
    }
    m_coms = lstComs;
    emit comChanged();
}
