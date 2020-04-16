
#include "SerialPortIO.h"
#include "ICustomIO.h"
#include <QDebug>

namespace CustomIO {
    SerialPortIO::SerialPortIO()
    {

    }

    QByteArray SerialPortIO::getData()
    {
        return nullptr;
    }

    int SerialPortIO::writeData(QByteArray cmd)
    {
        if(!m_serialPort->isOpen())
        {
            return -1;
        }
        m_serialPort->write(cmd);
        m_serialPort->waitForBytesWritten(1000);
        return 0;
    }

    int SerialPortIO::Open()
    {
        m_serialPort = make_unique<QSerialPort>();
        m_serialPort->setPortName(m_data.ComName);
        m_serialPort->setBaudRate(m_data.baudRate);
        m_serialPort->setParity(m_data.parity);
        m_serialPort->setDataBits(m_data.databits);
        m_serialPort->setStopBits(m_data.stopbits);

        connect(m_serialPort.get(), SIGNAL(readyRead()), this, SLOT(ReadData()));

        int ret = m_serialPort->open(QIODevice::ReadWrite) ? 0 : -1;
        qDebug() << "m_serialPort->open:" << ret;
        return ret;
    }

    int SerialPortIO::Init(QStringList configData)
    {
        m_data.ComName = configData.at(0);
        m_data.baudRate = QSerialPort::BaudRate(configData.at(1).toInt());
        m_data.parity = QSerialPort::Parity(configData.at(2).toInt());
        m_data.databits = QSerialPort::DataBits(configData.at(3).toInt());
        m_data.stopbits = QSerialPort::StopBits(configData.at(4).toInt());

        qDebug() << "baudRate:" << m_data.baudRate;
        return 0;
    }

    void SerialPortIO::ReadData()
    {
        m_buffer = m_serialPort->readAll();
        emit sigSendData(m_buffer);
    }

    void SerialPortIO::Close()
    {
        m_serialPort->close();
    }
}

