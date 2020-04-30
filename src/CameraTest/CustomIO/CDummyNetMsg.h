#ifndef CDUMMYNETMSG_H
#define CDUMMYNETMSG_H
#include <QObject>

class CDummyNetMsg: public QObject
{
    Q_OBJECT

signals:
    int sig_SocketWriteData(QByteArray cmd);
    int sig_SocketOpen();
    void sig_SocketClose();

public:
    CDummyNetMsg();
    int WriteData(QByteArray cmd);
    int Open();
    void Close();

};

#endif // CDUMMYNETMSG_H
