#include "ReadParser.h"
#include <QDebug>

ReadParser::ReadParser()
{

}

int ReadParser::ParseData(QByteArray data, struPacketData& packet)
{
    int ret = -1;
    int dataStart;
    QString packetHead, packetEnd;
    int packetHeadSize, packetEndSize;

    if(data.contains("StrHead:") && data.contains(":ImageIDEnd"))
    {
        ret = 0;
        packetHead = "StrHead:";
        packetEnd = ":ImageIDEnd";
        packetHeadSize = packetHead.length();
        packetEndSize = packetEnd.length();

        dataStart = data.indexOf(packetHead);
        packet.cmd = enumCmd::READ_IMAGE;
        packet.endPos = data.indexOf(packetEnd) + packetEndSize;
        QByteArray packData = data.mid(dataStart, packet.endPos - dataStart);
        qDebug() << "packData:" << packData;
        packet.data.append(packData);
    }
    else if(data.contains("Subscribe()0"))
    {
        ret = 0;
        packet.cmd = enumCmd::SUBSCRIBE;
    }

    return ret;
}
