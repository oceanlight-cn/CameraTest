
#ifndef __SerialPortIO_h__
#define __SerialPortIO_h__

#include "ICustomIO.h"
#include "globaldef.h"
#include <memory>

using namespace std;

namespace CustomIO
{
    class SerialPortIO: public ICustomIO
    {
        Q_OBJECT

    public:
        SerialPortIO();

        virtual QByteArray getData();
        virtual int Init(QStringList configData);

    private:
        struSerialData m_data;
        unique_ptr<QSerialPort> m_serialPort = nullptr;
        QByteArray m_buffer;

    public slots:
        virtual int writeData(QByteArray cmd);
        virtual int Open();
        virtual void Close();
        virtual void ReadData();
	};
}

#endif
