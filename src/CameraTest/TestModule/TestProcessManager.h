#ifndef TESTPROCESSMANAGER_H
#define TESTPROCESSMANAGER_H

#include "CustomIO/ICustomIO.h"
#include "CustomIO/IOFactory.h"
#include "CustomIO/NetIO.h"
#include <QThread>
#include "CustomIoReadProcessor.h"
#include "Queue/ReadQueueThread.h"
#include <QObject>
#include "CustomIO/DataSource.h"
#include "CustomIO/DataSourceManager.h"
#include "CustomIO/TriggerSource.h"
#include "CustomIO/TriggerSourceManager.h"
#include <QTimer>
#include <atomic>
#include <QSemaphore>
#include <vector>
#include <QMutex>
#include <map>

#include <chrono>
#include <queue>
#include <memory>
#include "CustomIO/CDummyNetMsg.h"
#include "CustomIO/CDummySerialportMsg.h"

using namespace std;

struct struCustomIoProcesser
{
    shared_ptr<CustomIO::ICustomIO> pObjCustomIo;
    shared_ptr<QThread> pIoThread;
    shared_ptr<QThread> pReadQueueThread;
    shared_ptr<CustomIoReadProcessor> pCustomIoReadProcessor;
    shared_ptr<ReadQueueThread> pReadQueue;
};

enum class CommState
{
    INITED,
    SUBSCRIBED,
};

class TestProcessManager : public QObject
{
    Q_OBJECT

public:
    explicit TestProcessManager(QObject* parent = nullptr);
    ~TestProcessManager();

    void Init();
    void ReadImage();

    void SetConfig(struTestConfig config);

    void SetDataSourcesConfig(struDataSourceConfig config);
    void SetTriggerSourcesConfig(struTriggerSourceConfig config);

    void Stop();

private:
    shared_ptr<CustomIO::ICustomIO> m_pObjCustomNetIo;
    CustomIO::NetIO* m_p_objNetIo;
    QThread* m_pNetThread;
    QThread* m_pReadQueueThread;
    shared_ptr<CustomIoReadProcessor> m_pCustomIoReadProcessor;
    shared_ptr<ReadQueueThread> m_clsReadQueue;

    map<enumDataSource, struCustomIoProcesser> m_mapCustomIoProcesser;

    static struDataSourceConfig m_DataSourceConfigData;
    static struTriggerSourceConfig m_TriggerSourceConfigData;

    unique_ptr<DataSourceManager> m_DataSourceManager;
    unique_ptr<TriggerSourceManager> m_TriggerSourceManager;

    atomic_bool m_bTerminated {false};
    atomic_bool m_bIsRunning {false};

    struTestConfig m_TestConfig;

    QSemaphore m_WaitReadCodeBack, m_WaitSubscribe;
    QMutex mutex, mutexAddQueue;

    vector<pair<QByteArray, enumDataSource> > m_vecDecodeData;
    QTimer* timeProcess;

    int m_TriggerTimes = 0;
    int m_DecodeTimes = 0;

    enumTriggerSource m_struTriggerSource;

    unique_ptr<IOFactory> m_objIoFactory;

    void Subscribe();

    bool m_bIsConnected = false;
    bool m_bInited = false;

    CommState m_commState;
    CDummyNetMsg netMsg;
    CDummySerialportMsg serialportMsg;

signals:
    void recvDateDisplay(QByteArray str, enumDataSource src);
    void sendImageInfo(QString netImageWorkEntry, enumDataSource src);
    void sig_recvDateDisplay(QByteArray str, enumDataSource src);
    void sig_disconnected(CustomIO::enumIoType io_type);

public slots:
    void slot_recvDateDisplay(QByteArray str, enumDataSource src);
    void slot_sendImageInfo(QString netImageWorkEntry, enumDataSource src);
    void slot_sendImageOKCount(int NetOKCount, enumDataSource src);
    void slotTimeout();
    void Process();

    void slotGetTrigger();
    void slot_recvSubscribe();
};

#endif // TESTPROCESSMANAGER_H
