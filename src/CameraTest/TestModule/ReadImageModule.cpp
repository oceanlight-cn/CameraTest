﻿#include "ReadImageModule.h"
#include <QDebug>
#include <QDateTime>

ReadImageModule::ReadImageModule()
{

}

void ReadImageModule::ProcessData(QByteArray data)
{
    qDebug() << "emit recvDateDisplay";

    QByteArray strAllValue = data;

    QList<QString> MsgList;

    if (strAllValue.contains("StrHead:") && strAllValue.contains(":StrEnd"))
    {
        int size = QString("StrHead:").length();
        QString barStr = strAllValue.mid(strAllValue.indexOf("StrHead:") + size , strAllValue.indexOf(":StrEnd") - strAllValue.indexOf("StrHead:") - size);
        QString TemplateStr = getTemplateStr();

        MsgList.push_back("OK");

    }
    if (strAllValue.contains("CenterHead:") && strAllValue.contains(":CenterEnd"))
    {
        int size = QString("CenterHead:").length();
        QString barCenter = strAllValue.mid(strAllValue.indexOf("CenterHead:") + size , strAllValue.indexOf(":CenterEnd") - strAllValue.indexOf("CenterHead:") - size);
        QStringList dataListCenter =  barCenter.split(",");
        double BarCenterX,BarCenterY;
        if (dataListCenter.size() == 2)
        {
            BarCenterX = dataListCenter.at(0).toDouble();
            BarCenterY = dataListCenter.at(1).toDouble();            
        }

        QByteArray byteCenter;
        byteCenter = barCenter.toLatin1();
        emit recvDateDisplay(byteCenter);

        MsgList.push_back("OK");

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
