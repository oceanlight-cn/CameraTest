#include "CDummySerialportMsg.h"

CDummySerialportMsg::CDummySerialportMsg()
{

}

int CDummySerialportMsg::WriteData(QByteArray cmd)
{
    emit sig_SerialWriteData(cmd);
    return 0;
}

int CDummySerialportMsg::Open()
{
    emit sig_SerialOpen();
    return 0;
}

void CDummySerialportMsg::Close()
{
    emit sig_SerialClose();
}
