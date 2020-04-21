#ifndef READQUEUETHREAD_H
#define READQUEUETHREAD_H

#include <queue>
#include <memory>
#include <QObject>

#include <mutex>
#include <condition_variable>

using namespace std;

class ReadQueueThread : public QObject
{
    Q_OBJECT

public:
    ReadQueueThread();
    queue<QByteArray>* getQueue();

    shared_ptr<std::condition_variable> getData_cond() const;

public slots:
    void slotReceiveData(QByteArray data);

private:
    queue<QByteArray>* queue_data;
    std::mutex mut;
    shared_ptr<std::condition_variable> m_data_cond;
};


#endif // READQUEUETHREAD_H
