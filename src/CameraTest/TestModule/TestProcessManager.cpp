#include "TestProcessManager.h"
#include <QDebug>
#include <QThread>
#include <functional>
#include <chrono>
#include <future>
#include <thread>
#include "Helper/EnumTypeConverter.h"
#include "Helper/LaterTimer.hpp"

using namespace std::chrono;

struDataSourceConfig TestProcessManager::m_DataSourceConfigData;
struTriggerSourceConfig TestProcessManager::m_TriggerSourceConfigData;
TestProcessManager::TestProcessManager(QObject* parent)
    :QObject(parent)
{
    m_DataSourceManager = make_unique<DataSourceManager>();
    m_TriggerSourceManager = make_unique<TriggerSourceManager>();

    qDebug() << "TestProcessManager";

    qRegisterMetaType<enumDataSource>("enumDataSource");

}

TestProcessManager::~TestProcessManager()
{
    qDebug() << "~TestProcessManager";
}

void TestProcessManager::Init(QString strTriggerCmd, QString TemplateStr, QString CenterStr, QString CoordinateX, QString CoordinateY)
{
    m_TestConfig.triggerCmd = strTriggerCmd + "\r\n";

    m_bTerminated.store(false);

    vector<shared_ptr<DataSource>> vecDataSources = m_DataSourceManager->getDataSources();
    for (int i = 0; i < vecDataSources.size(); ++i) {
//        struCustomIoProcesser* pobjCustomIoProcesser = new struCustomIoProcesser();
        struCustomIoProcesser objCustomIoProcesser;
        shared_ptr<DataSource> pDataSource = vecDataSources[i];
        enumIoType dataSourceType =  EnumTypeConverter::ConvertDataSource2Type(pDataSource->getType());

        objCustomIoProcesser.pObjCustomIo =  pDataSource->getCustomIO();
        objCustomIoProcesser.pIoThread = make_shared<QThread>();
        objCustomIoProcesser.pObjCustomIo->moveToThread(objCustomIoProcesser.pIoThread.get());
        objCustomIoProcesser.pIoThread->start();

        connect(this, SIGNAL(destroyed(QObject*)), objCustomIoProcesser.pObjCustomIo.get(), SLOT(deleteLater()));

        objCustomIoProcesser.pReadQueueThread = make_shared<QThread>();
        objCustomIoProcesser.pReadQueue = make_shared<ReadQueueThread>();
        objCustomIoProcesser.pReadQueue->moveToThread(objCustomIoProcesser.pReadQueueThread.get());
        objCustomIoProcesser.pReadQueueThread->start();

        connect(objCustomIoProcesser.pObjCustomIo.get(), SIGNAL(sigSendData(QByteArray)), objCustomIoProcesser.pReadQueue.get(), SLOT(slotReceiveData(QByteArray)));

        objCustomIoProcesser.pCustomIoReadProcessor = make_shared<CustomIoReadProcessor>(objCustomIoProcesser.pObjCustomIo, objCustomIoProcesser.pReadQueue, TemplateStr, CenterStr, CoordinateX, CoordinateY);
        objCustomIoProcesser.pCustomIoReadProcessor->start();

        connect(objCustomIoProcesser.pCustomIoReadProcessor.get(), SIGNAL(sig_recvDateDisplay(QByteArray,enumDataSource)), this, SLOT(slot_recvDateDisplay(QByteArray,enumDataSource)));
        connect(objCustomIoProcesser.pCustomIoReadProcessor.get(), SIGNAL(sendImageInfo(QString,enumDataSource)), this, SLOT(slot_sendImageInfo(QString,enumDataSource)));
        connect(objCustomIoProcesser.pCustomIoReadProcessor.get(), SIGNAL(sendImageOKCount(int,enumDataSource)), this, SLOT(slot_sendImageOKCount(int,enumDataSource)));

        connect(objCustomIoProcesser.pCustomIoReadProcessor.get(), SIGNAL(sig_recvSubscribe()), this, SLOT(slot_recvSubscribe()));

        switch (dataSourceType) {
        case enumIoType::ETHERNET:
            {
                connect(this, SIGNAL(sig_SocketWriteData(QByteArray)), objCustomIoProcesser.pObjCustomIo.get(), SLOT(writeData(QByteArray)));
                connect(this, SIGNAL(sig_SocketOpen()), objCustomIoProcesser.pObjCustomIo.get(), SLOT(Open()));
                connect(this, SIGNAL(sig_SocketClose()), objCustomIoProcesser.pObjCustomIo.get(), SLOT(Close()));

                emit sig_SocketOpen();
                QThread::msleep(1000);
                m_commState = CommState::INITED;
                Subscribe();
                QThread::msleep(1000);

            }
            break;
        case enumIoType::SERIAL_PORT:
            {
                connect(this, SIGNAL(sig_SerialWriteData(QByteArray)), objCustomIoProcesser.pObjCustomIo.get(), SLOT(writeData(QByteArray)));
                connect(this, SIGNAL(sig_SerialOpen()), objCustomIoProcesser.pObjCustomIo.get(), SLOT(Open()));
                connect(this, SIGNAL(sig_SerialClose()), objCustomIoProcesser.pObjCustomIo.get(), SLOT(Close()));

                emit sig_SerialOpen();
            }
            break;

        default:
            break;
        }

        m_mapCustomIoProcesser.insert(make_pair(pDataSource->getType(), objCustomIoProcesser));
    }

}

void TestProcessManager::ReadImage()
{

}

void TestProcessManager::SetConfig(struTestConfig config)
{
    m_TestConfig.cameraIp = config.cameraIp;
    m_TestConfig.port = config.port;
    m_TestConfig.triggerCmd = config.triggerCmd;
}

void TestProcessManager::SetDataSourcesConfig(struDataSourceConfig config)
{
    memcpy(&m_DataSourceConfigData.serialPortConfig, &config.serialPortConfig, sizeof(struSerialData));
    m_DataSourceConfigData.dataSources = config.dataSources;
}

void TestProcessManager::SetTriggerSourcesConfig(struTriggerSourceConfig config)
{
    memcpy(&m_TriggerSourceConfigData, &config, sizeof(struTriggerSourceConfig));

    QStringList lstConfig;

    m_DataSourceManager->Clear();
    for (int i = 0; i < m_DataSourceConfigData.dataSources.size(); ++i) {
        shared_ptr<DataSource> pDataSource = make_shared<DataSource>();
        qDebug() << "TriggerSource:" << int(m_DataSourceConfigData.dataSources[i]);
        lstConfig.clear();

        switch(m_DataSourceConfigData.dataSources[i])
        {
            case enumDataSource::ETHERNET:
                #ifdef TEST
                    lstConfig << "192.168.1.109" << "2000";
                #else
                    lstConfig << m_TestConfig.cameraIp << QString::number(m_TestConfig.port);
                #endif
                qDebug() << "ip:" << m_TestConfig.cameraIp;
                pDataSource->Init(enumDataSource::ETHERNET, lstConfig);

            break;
            case enumDataSource::SERIAL_PORT:
                lstConfig << m_DataSourceConfigData.serialPortConfig.ComName
                          << QString::number(int(m_DataSourceConfigData.serialPortConfig.baudRate))
                          << QString::number(int(m_DataSourceConfigData.serialPortConfig.parity))
                          << QString::number(int(m_DataSourceConfigData.serialPortConfig.databits))
                          << QString::number(int(m_DataSourceConfigData.serialPortConfig.stopbits));
                pDataSource->Init(enumDataSource::SERIAL_PORT, lstConfig);
            break;

        }

        m_DataSourceManager->AddDataSource(std::move(pDataSource));
    }

    m_TriggerSourceManager->Init(m_TriggerSourceConfigData, m_DataSourceConfigData.dataSources);

    m_bInited = true;
}

void TestProcessManager::Process()
{
    qDebug() << "TestProcessManager Process thread:" << QThread::currentThreadId();
    m_DecodeTimes = 0;

    QString StartImage = QString("StartCacheImage\r\n");// info camera to cache images
    emit sig_SocketWriteData(StartImage.toLatin1());

    while(!m_bTerminated.load())
    {
        if(m_bInited) //Add
        {
            if(m_commState != CommState::SUBSCRIBED)
            {
                qDebug() << "not receive subscribe.";
                continue;
            }

            m_struTriggerSource = m_TriggerSourceManager->getTriggerSource()->getType();
            QString strTriggerCmd = m_TestConfig.triggerCmd;

            int checkTime = 1000;

            later later_test1(checkTime, true, std::bind(&TestProcessManager::slotTimeout,this));

            switch (m_struTriggerSource) {
                case enumTriggerSource::ETHERNET:
                        qDebug() << "trigger cmd:" << strTriggerCmd;
                        emit sig_SocketWriteData(strTriggerCmd.toLatin1());
                        m_WaitReadCodeBack.acquire();
                    break;
                case enumTriggerSource::SERIAL_PORT:
                    emit sig_SerialWriteData(strTriggerCmd.toLatin1());
                    m_WaitReadCodeBack.acquire();
                break;

            default:
                break;
            }
        }
        if(m_bTerminated.load()) break;
    }
}

void TestProcessManager::slotGetTrigger()
{
    m_TriggerTimes++;
}

void TestProcessManager::slot_recvSubscribe()
{
    m_commState = CommState::SUBSCRIBED;
}

void TestProcessManager::Stop()
{
    emit sig_SocketClose();
    if(m_mapCustomIoProcesser.size() > 0)
    {
        auto it = m_mapCustomIoProcesser.begin();
        for (; it != m_mapCustomIoProcesser.end(); ++it) {
            it->second.pIoThread->quit();
            it->second.pIoThread->wait();

            it->second.pReadQueueThread->quit();
            it->second.pReadQueueThread->wait();

            it->second.pCustomIoReadProcessor->Stop();
            it->second.pCustomIoReadProcessor->quit();
            it->second.pCustomIoReadProcessor->wait();
        }
        m_mapCustomIoProcesser.clear();
    }

    m_bTerminated.store(true);
    m_WaitReadCodeBack.release(m_WaitReadCodeBack.available());
}

void TestProcessManager::Subscribe()
{
    QString MsgContent = R"(<Message><data data="1"/><data data="StrHead:"/><data data="[barCode.CodeStr]"/><data data=":StrEnd"/><data data=";"/><data data="CenterHead:"/><data data="[barCode.Center_X]"/><data data=","/><data data="[barCode.Center_Y]"/><data data=":CenterEnd"/><data data=";"/><data data="ImageIDHead:"/><data data="[barCode.ImageID]"/><data data=":ImageIDEnd"/><data data="&lt;CR>"/><data data="&lt;LF>"/></Message>)";
    QString MsgData = QString("Subscribe(%1)\r\n").arg(MsgContent);
    emit sig_SocketWriteData(MsgData.toLatin1());
}

void TestProcessManager::slotTimeout()
{
    qDebug() << "slotTimeout";

    if(m_vecDecodeData.size() >= m_DataSourceManager->getDataSources().size())
    {
        qDebug() << "get all datasources";
        emit recvDateDisplay(m_vecDecodeData[0].first, m_vecDecodeData[0].second);
        m_vecDecodeData.clear();
    }

    m_WaitReadCodeBack.release();
}

void TestProcessManager::slot_recvDateDisplay(QByteArray str, enumDataSource src)
{
    qDebug() << "TestProcessManager::slot_recvDateDisplay";
    QMutexLocker locker(&mutex);

    if(src == enumDataSource::ETHERNET)
    {
        m_DecodeTimes++;
    }
    m_vecDecodeData.push_back(make_pair(str, src));

    emit sig_recvDateDisplay(str, src);
}

void TestProcessManager::slot_sendImageInfo(QString netImageWorkEntry, enumDataSource src)
{
    if(src == enumDataSource::ETHERNET)
    {
        QStringList lstImageInfo = netImageWorkEntry.split(";");
        QString ImagID = lstImageInfo[lstImageInfo.size() - 1];
        qDebug() << "ImageId:" << ImagID;
        if(!ImagID.isEmpty())
        {
            QString SaveImagID =  "SaveImageByID(%1)\r\n"; //info camera to save images
            SaveImagID = SaveImagID.arg(ImagID); //0001;
            emit sig_SocketWriteData(SaveImagID.toLatin1());
        }
    }

    emit sendImageInfo(netImageWorkEntry, src);
}

void TestProcessManager::slot_sendImageOKCount(int NetOKCount, enumDataSource src)
{

}
