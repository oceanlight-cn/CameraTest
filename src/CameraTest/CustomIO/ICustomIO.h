#include <exception>
using namespace std;

#ifndef __ICustomIO_h__
#define __ICustomIO_h__

#include <QByteArray>
#include <QStringList>
#include <QObject>

#include <mutex>
#include <condition_variable>

namespace CustomIO
{
    enum class enumIoType
    {
        ETHERNET,
        SERIAL_PORT,
    };

    class ICustomIO : public QObject
	{
        Q_OBJECT

    public:
            virtual QByteArray getData() = 0;
            virtual int Init(QStringList configData) = 0;

            virtual enumIoType getIo_type() const;
            virtual void setIo_type(const enumIoType &io_type);

            virtual bool getIsEnable() const;
            virtual void setIsEnable(bool isEnable);

            virtual ~ICustomIO();

    protected:
            enumIoType m_io_type;
            bool m_isEnable;
            QStringList m_configData;

            virtual void ReadData() = 0;

    public slots:
            virtual int writeData(QByteArray cmd) = 0;
            virtual int Open() = 0;
            virtual void Close() = 0;

    signals:
            void sigSendData(QByteArray data);
            void sigDisconnected(enumIoType io_type);
    };
}

#endif
