
#include "NetIO.h"
#include <QDebug>
#include <QThread>
#include <QSettings>


namespace CustomIO {
    QByteArray NetIO::getData()
    {
        return m_buffer;
    }

    int NetIO::writeData(QByteArray cmd) noexcept
    {
            if (m_client->state() != QAbstractSocket::ConnectedState)
            {
                qDebug() << "socket disconnected.";
                emit sigDisconnected(m_io_type);
                return -1;
            }
            else
            {
                m_client->write(cmd);
                m_client->waitForBytesWritten(1000);
            }

        return 0;
    }

    int NetIO::Init(QStringList configData)
    {
        int ret = -1;

        if(configData.size() != 2)
        {
            qDebug() << "NetIo parameter size error";
            return ret;
        }

        m_ip = configData.at(0);
        m_port = configData.at(1).toInt();

        ret = 0;
        return ret;
    }

    int NetIO::Open() noexcept
    {
        if(m_client != nullptr)
        {
            if(IsConnected())
            {
                return 0;
            }
        }

        qDebug() << "NetIO::Open(), thread:" << QThread::currentThread();

        m_client.reset(new QTcpSocket);

        m_client->connectToHost(m_ip, m_port);
        if(!m_client->waitForConnected(1000))
        {
            return -1;
        }
        connect(m_client.get(), SIGNAL(readyRead()), this, SLOT(ReadData()));
        connect(m_client.get(), static_cast<void(QAbstractSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error),

                        this, &NetIO::SocketError);

        return 0;
    }

    bool NetIO::IsConnected()
    {
        return m_client->state() == QTcpSocket::ConnectedState;
    }

    void NetIO::Close()
    {
        m_client->abort();
        m_client->disconnectFromHost();
    }

    void NetIO::SocketError()
    {
        qDebug() << "socket error.";
    }

    NetIO::NetIO()
    {

    }

    NetIO::~NetIO()
    {
        qDebug() << "NetIO::~NetIO(), thread:" << QThread::currentThread();
    }

    void NetIO::ReadData()
    {
        qDebug() << "isconnected:" << IsConnected();

        m_buffer = m_client->readAll();
        qDebug() << "ReadData:" << m_buffer;
        emit sigSendData(m_buffer);
    }
}



