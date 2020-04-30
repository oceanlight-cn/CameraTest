#include "CDummyNetMsg.h"

CDummyNetMsg::CDummyNetMsg()
{

}

int CDummyNetMsg::WriteData(QByteArray cmd)
{
    emit sig_SocketWriteData(cmd);
    return 0;
}

int CDummyNetMsg::Open()
{
    emit sig_SocketOpen();
    return 0;
}

void CDummyNetMsg::Close()
{
    emit sig_SocketClose();
}
