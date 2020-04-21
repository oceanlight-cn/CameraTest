#include "ReadImageModule.h"
#include <QDebug>
#include <QDateTime>

ReadImageModule::ReadImageModule()
{

}

void ReadImageModule::ProcessData(QByteArray data)
{
    qDebug() << "emit recvDateDisplay";

    QByteArray strAllValue = data;

    emit recvDateDisplay(strAllValue);
    QList<QString> MsgList;

    if (strAllValue.contains("StrHead:") && strAllValue.contains(":StrEnd"))
    {
        int size = QString("StrHead:").length();
        QString barStr = strAllValue.mid(strAllValue.indexOf("StrHead:") + size , strAllValue.indexOf(":StrEnd") - strAllValue.indexOf("StrHead:") - size);
        QString TemplateStr = getTemplateStr();
        if(TemplateStr == barStr)
        {
            MsgList.push_back("OK");
        }
        else
        {
            MsgList.push_back(barStr);
        }
    }
    if (strAllValue.contains("CenterHead:") && strAllValue.contains(":CenterEnd"))
    {
        int size = QString("CenterHead:").length();
        QString barCenter = strAllValue.mid(strAllValue.indexOf("CenterHead:") + size , strAllValue.indexOf(":CenterEnd") - strAllValue.indexOf("CenterHead:") - size);
        QStringList dataListCenter =  barCenter.split(",");
        double BarCenterX,BarCenterY;
        double CenterX,CenterY;
        if (dataListCenter.size() == 2)
        {
            BarCenterX = dataListCenter.at(0).toDouble();
            BarCenterY = dataListCenter.at(1).toDouble();
        }
        QString strCenter = getCenterStr();
        QStringList Centerlist =  strCenter.split(",");
        if (Centerlist.size() == 2)
        {
            CenterX = Centerlist.at(0).toDouble();
            CenterY = Centerlist.at(1).toDouble();
        }
        double offsetX = getCoordinateX().toDouble();
        double offsetY = getCoordinateY().toDouble();
        if((BarCenterX >= CenterX-offsetX) && (BarCenterX <= CenterX+offsetX) && (BarCenterY >=CenterY-offsetY) && (BarCenterY <= CenterY+offsetY))
        {
            MsgList.push_back("OK");
        }
        else
        {
            QString centerXY = QString("%1,%2").arg(BarCenterX).arg(BarCenterY);
            MsgList.push_back(centerXY);
        }
    }
    if (strAllValue.contains("ImageIDHead:") && strAllValue.contains(":ImageIDEnd"))
    {
        int size = QString("ImageIDHead:").length();
        QString ImageByID = strAllValue.mid(strAllValue.indexOf("ImageIDHead:") + size , strAllValue.indexOf(":ImageIDEnd") - strAllValue.indexOf("ImageIDHead:") - size);
        MsgList.push_back(ImageByID);
    }

    if(MsgList[0] == "OK" && MsgList[1] == "OK")
    {

    }
    else
    {
        QString imageInfo;
        imageInfo += QString::number(1);
        imageInfo +=";";
        imageInfo +=MsgList[0];
        imageInfo +=";";
        imageInfo +=MsgList[1];
        imageInfo +=";";
        QDateTime time = QDateTime::currentDateTime();
        QString timeStr = time.toString("yyyy-MM-dd hh:mm:ss:zzz");
        imageInfo +=timeStr;
        imageInfo +=";";
        imageInfo +=MsgList[2];

        emit sendImageInfo(imageInfo);
    }
    qDebug() << "MsgList:" << MsgList;
}
