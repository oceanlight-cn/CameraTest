#include "ReadQueueThread.h"
#include <QDebug>

ReadQueueThread::ReadQueueThread()
{
    queue_data = new queue<QByteArray>();
    m_data_cond = make_shared<std::condition_variable>();
}


queue<QByteArray>* ReadQueueThread::getQueue()
{
    return queue_data;
}

void ReadQueueThread::slotReceiveData(QByteArray data)
{
    std::lock_guard<std::mutex> lk(mut);
    qDebug() << "receive";
    queue_data->push(data);
    m_data_cond->notify_one();
}

shared_ptr<std::condition_variable> ReadQueueThread::getData_cond() const
{
    return m_data_cond;
}
