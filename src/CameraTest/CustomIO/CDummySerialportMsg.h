#ifndef CDUMMYSERIALPORTMSG_H
#define CDUMMYSERIALPORTMSG_H
#include <QObject>

class CDummySerialportMsg: public QObject
{
    Q_OBJECT

signals:
    int sig_SerialWriteData(QByteArray cmd);
    int sig_SerialOpen();
    void sig_SerialClose();

public:
    CDummySerialportMsg();
    int WriteData(QByteArray cmd);
    int Open();
    void Close();

};

#endif // CDummySerialportMsg_H
