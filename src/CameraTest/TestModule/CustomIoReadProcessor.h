#ifndef CUSTOMIOREADPROCESSOR_H
#define CUSTOMIOREADPROCESSOR_H

#include <QThread>
#include <atomic>

#include <mutex>
#include <condition_variable>
#include <memory>
#include <QByteArray>
#include "CustomIO/ICustomIO.h"
#include "Queue/ReadQueueThread.h"
#include <QDebug>
#include "Queue/ReadParser.h"
#include "TestModule/ReadImageModule.h"

using namespace std;

Q_DECLARE_METATYPE(enumDataSource)

class CustomIoReadProcessor : public QThread
{
    Q_OBJECT

public:
    explicit CustomIoReadProcessor(const shared_ptr<CustomIO::ICustomIO> &io, const shared_ptr<ReadQueueThread> &readQueue, QString TemplateStr, QString CenterStr, QString CoordinateX, QString CoordinateY);

    void run();

    void Stop();

private:
    atomic_bool m_bTeminated { false };
    std::mutex mut;

    shared_ptr<CustomIO::ICustomIO> m_io;
    shared_ptr<ReadQueueThread> m_ReadQueue;
    QByteArray m_buff;
    unique_ptr<ReadParser> m_ReadParser;
    unique_ptr<ReadImageModule> m_ReadImageModule;

    enumDataSource m_typeDataSource;

    QString m_TemplateStr;
    QString m_CenterStr;
    QString m_CoordinateX;
    QString m_CoordinateY;

signals:
      void sig_recvDateDisplay(QByteArray str, enumDataSource src);
      void sendImageInfo(QString netImageWorkEntry, enumDataSource src);
      void sendImageOKCount(int NetOKCount, enumDataSource src);
      void sig_recvSubscribe();

public slots:
    void slot_recvDateDisplay(QByteArray str);
    void slot_sendImageInfo(QString netImageWorkEntry);
};

#endif // CUSTOMIOREADPROCESSOR_H
