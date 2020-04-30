#include "CameraTest.h"
#include <QDebug>

CameraTest::CameraTest()
{

}

bool CameraTest::EthernetSet() const
{
    return m_isEthernetSet;
}

bool CameraTest::SerialportSet() const
{
    return m_isSerialportSet;
}

void CameraTest::StartTest()
{
    double Hour = m_duration;
    int msec = Hour*60*60*1000;

    m_reachDateTime = QDateTime::currentDateTime().addMSecs(msec);

    m_timer.reset(new QTimer);
    m_timer->setInterval(1000);
    connect(m_timer.get(),SIGNAL(timeout()),this,SLOT(updateTime()));

    InitConfigs();
    m_TestProcessManager.reset(new TestProcessManager);
    connect(m_TestProcessManager.get(), SIGNAL(recvDateDisplay(QByteArray,enumDataSource)), this, SLOT(RecvDateDisplay(QByteArray,enumDataSource)));
    connect(m_TestProcessManager.get(), SIGNAL(sendImageInfo(QString,enumDataSource)), this, SLOT(RecvImageInfo(QString,enumDataSource)));
    m_TestProcessManager->SetConfig(m_testConfig);
    m_TestProcessManager->SetDataSourcesConfig(m_DataSourceConfig);
    m_TestProcessManager->SetTriggerSourcesConfig(m_TriggerSourceConfig);
    m_TestProcessManager->Init();
}

void CameraTest::StopTest()
{
    m_TestProcessManager->Stop();
}

int CameraTest::getPort() const
{
    return m_port;
}

QString CameraTest::getIp() const
{
    return m_ip;
}

void CameraTest::setEthernetSet(bool isEthernetSet)
{
    m_isEthernetSet = isEthernetSet;
}

void CameraTest::setSerialportSet(bool isSerialportSet)
{
    m_isSerialportSet = isSerialportSet;
}

void CameraTest::setPort(int port)
{
    m_port = port;
}

void CameraTest::setIp(QString ip)
{
    m_ip = ip;
}

void CameraTest::updateTime()
{
    if(QDateTime::currentDateTime() > m_reachDateTime)
    {
        StopTest();
    }
}

void CameraTest::RecvDateDisplay(QByteArray str, enumDataSource src)
{
    qDebug() << "RecvDateDisplay";
    QString strPos = QString::fromLatin1(str);
    emit sendCoordinate(strPos);
}

void CameraTest::RecvImageInfo(QString netImageWorkEntry, enumDataSource src)
{
    emit increaseFailCount();
}

void CameraTest::InitConfigs()
{
    m_testConfig.cameraIp = m_ip;
    m_testConfig.port = m_port;

    m_DataSourceConfig.dataSources.clear();
    if(m_isEthernetSet)
    {
        enumDataSource src = enumDataSource::ETHERNET;
        m_DataSourceConfig.dataSources.push_back(src);
    }
    if(m_isSerialportSet)
    {
        enumDataSource src = enumDataSource::SERIAL_PORT;
        m_DataSourceConfig.dataSources.push_back(src);
        SetSerialConfig(m_DataSourceConfig.serialPortConfig);
    }

    m_TriggerSourceConfig.triggerSource = enumTriggerSource::ETHERNET;

}

void CameraTest::SetSerialConfig(struSerialData &data)
{
    int BaudRate = m_baudrate;
    switch (BaudRate)
    {
    case 1200:
        data.baudRate = QSerialPort::Baud1200;
        break;
    case 2400:
        data.baudRate = QSerialPort::Baud2400;
        break;
    case 4800:
        data.baudRate = QSerialPort::Baud4800;
        break;
    case 9600:
        data.baudRate = QSerialPort::Baud9600;
        break;
    case 19200:
        data.baudRate = QSerialPort::Baud19200;
        break;
    case 38400:
        data.baudRate = QSerialPort::Baud38400;
        break;
    case 57600:
        data.baudRate = QSerialPort::Baud57600;
        break;
    case 115200:
        data.baudRate = QSerialPort::Baud115200;
        break;
    default:
        break;
    }

    QString Parity = m_parity;
    char chParity = Parity.toStdString().c_str()[0];
    switch((int)chParity)
    {
    case (int)'N':
        data.parity = QSerialPort::NoParity;
        break;
    case (int)'E':
        data.parity = QSerialPort::EvenParity;
        break;
    case (int)'O':
        data.parity = QSerialPort::OddParity;
        break;
    case (int)'M':
        data.parity = QSerialPort::MarkParity;
        break;
    case (int)'S':
        data.parity = QSerialPort::SpaceParity;
        break;
    default:
        break;
    }

    int Databits = m_databits;
    switch (Databits)
    {
    case 5:
        data.databits = QSerialPort::Data5;
        break;
    case 6:
        data.databits = QSerialPort::Data6;
        break;
    case 7:
        data.databits = QSerialPort::Data7;
        break;
    case 8:
        data.databits = QSerialPort::Data8;
        break;
    default:
        break;
    }

    int dataStop = (int) m_stopbits.toDouble()*2;
    switch(dataStop)
    {
    case 2:
        data.stopbits = QSerialPort::OneStop;
        break;
    case 3:
        data.stopbits = QSerialPort::OneAndHalfStop;
        break;
    case 4:
        data.stopbits = QSerialPort::TwoStop;
        break;
    default:
        break;
    }
}

QString CameraTest::getStopbits() const
{
    return m_stopbits;
}

void CameraTest::setStopbits(const QString &stopbits)
{
    m_stopbits = stopbits;
}

int CameraTest::getDatabits() const
{
    return m_databits;
}

void CameraTest::setDatabits(int databits)
{
    m_databits = databits;
}

QString CameraTest::getParity() const
{
    return m_parity;
}

void CameraTest::setParity(const QString &parity)
{
    m_parity = parity;
}

int CameraTest::getBaudrate() const
{
    return m_baudrate;
}

void CameraTest::setBaudrate(int baudrate)
{
    m_baudrate = baudrate;
}

QString CameraTest::getComport() const
{
    return m_comport;
}

void CameraTest::setComport(const QString &comport)
{
    m_comport = comport;
}

int CameraTest::getDuration() const
{
    return m_duration;
}

void CameraTest::setDuration(int duration)
{
    m_duration = duration;
}


