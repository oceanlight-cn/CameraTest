
#ifndef __NetIO_h__
#define __NetIO_h__

#include "ICustomIO.h"
#include <QTcpSocket>
#include <memory>
#include <QObject>
#include <QThread>
#include <QByteArray>

using namespace std;

namespace CustomIO
{
    class NetIO: public ICustomIO
    {
        Q_OBJECT

    public:
        virtual QByteArray getData();
        virtual int Init(QStringList configData);

        bool IsConnected();

        NetIO();
        ~NetIO();

    private:
        unique_ptr<QTcpSocket> m_client = nullptr;
        QString m_ip;
        int m_port;
        QByteArray m_buffer;

    public slots:
        virtual int writeData(QByteArray cmd) noexcept;
        virtual int Open() noexcept;
        virtual void Close();

        void SocketError();

    private slots:
        void ReadData();

	};
}

#endif
