﻿#ifndef GLOBALDEF_H
#define GLOBALDEF_H

#include <QByteArray>
#include <QSerialPort>
#include <vector>

using namespace std;

enum class enumDataSource
{
    ETHERNET,
    SERIAL_PORT,
    USB2_SERIAL_PORT,
    USB2_KEYBOARD,
};

enum class enumTriggerSource
{
    ETHERNET,
    SERIAL_PORT,
    USB2_SERIAL_PORT,
    GPIO,
    IN_TURN,
};

enum class enumCmd
{
    NONE,
    READ_IMAGE,
    SUBSCRIBE,
};

struct struPacketData
{
    enumCmd cmd;
    int endPos;
    QByteArray data;

    struPacketData()
    {
        cmd = enumCmd::NONE;
        endPos = 0;
    }
};

struct struSerialData
{
    QString ComName;
    QSerialPort::BaudRate baudRate;
    QSerialPort::Parity parity;
    QSerialPort::DataBits databits;
    QSerialPort::StopBits stopbits;
};

typedef struct
{
    QString device_name;
    bool isLog;
}struDeviceInfo;

struct struDataSourceConfig
{
    vector<enumDataSource> dataSources;
    struSerialData serialPortConfig;
    struSerialData usb2serialPortConfig;
    struDeviceInfo usb2keyboardConfig;
};

struct struIoData
{
    bool enabled;
    QString ip;

    struIoData()
    {
//        enabled = false;
//        ip = "";
    }
};

struct struTriggerSourceConfig
{
    enumTriggerSource triggerSource;
    struIoData io[2];
    int turn_time;
};

struct struTestConfig
{
    QString cameraIp;
    int     port;
    QString triggerCmd;
};

#endif // GLOBALDEF_H
