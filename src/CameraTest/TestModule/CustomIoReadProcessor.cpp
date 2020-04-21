#include "CustomIoReadProcessor.h"
#include "globaldef.h"
#include "Helper/EnumTypeConverter.h"
#include <chrono>

CustomIoReadProcessor::CustomIoReadProcessor(const shared_ptr<CustomIO::ICustomIO> &io, const shared_ptr<ReadQueueThread> &readQueue, QString TemplateStr, QString CenterStr, QString CoordinateX, QString CoordinateY)
    :m_io(io),
     m_ReadQueue(readQueue),
     m_CoordinateX(CoordinateX),
     m_CoordinateY(CoordinateY),
     m_TemplateStr(TemplateStr),
     m_CenterStr(CenterStr)
{
    m_ReadParser = make_unique<ReadParser>();
    m_ReadImageModule = make_unique<ReadImageModule>();

    m_typeDataSource = EnumTypeConverter::ConvertType2DataSource(io->getIo_type());

    connect(m_ReadImageModule.get(), SIGNAL(recvDateDisplay(QByteArray)), this, SLOT(slot_recvDateDisplay(QByteArray)));
    connect(m_ReadImageModule.get(), SIGNAL(sendImageInfo(QString)), this, SLOT(slot_sendImageInfo(QString)));
    connect(m_ReadImageModule.get(), SIGNAL(sendImageOKCount(int)), this, SLOT(slot_sendImageOKCount(int)));

}

void CustomIoReadProcessor::run()
{
    while(!m_bTeminated)
    {
        std::unique_lock<std::mutex> lk(mut);

        bool done = m_ReadQueue->getData_cond()->wait_for(lk, std::chrono::seconds(3), [=]{return !m_ReadQueue->getQueue()->empty();});
        if(m_bTeminated) break;

        if(!done) continue;

        if(!m_ReadQueue->getQueue()->empty())
        {
            qDebug() << "data:" << m_ReadQueue->getQueue()->front();
            m_buff.append(m_ReadQueue->getQueue()->front());
            m_ReadQueue->getQueue()->pop();

            struPacketData objPacketData;
            if(m_ReadParser->ParseData(m_buff, objPacketData) == 0)
            {
                m_buff.remove(0, objPacketData.endPos);
                qDebug() << "m_buff left:" << m_buff;
                if(objPacketData.cmd == enumCmd::READ_IMAGE)
                {
    #ifdef TEST
                    QString centerStr = "1,1";
                    QString cordX = "1.0";
                    QString cordY = "1.0";
                    QString TemplateStr = "abc";
                    m_ReadImageModule->setTemplateStr(TemplateStr);
                    m_ReadImageModule->setCenterStr(centerStr);
                    m_ReadImageModule->setCoordinateX(cordX);
                    m_ReadImageModule->setCoordinateY(cordY);
    #endif
                    m_ReadImageModule->setTemplateStr(m_TemplateStr);
                    m_ReadImageModule->setCenterStr(m_CenterStr);
                    m_ReadImageModule->setCoordinateX(m_CoordinateX);
                    m_ReadImageModule->setCoordinateY(m_CoordinateY);
                    m_ReadImageModule->ProcessData(objPacketData.data);
                }
                else if(objPacketData.cmd == enumCmd::SUBSCRIBE)
                {
                    emit sig_recvSubscribe();
                }
            }
            qDebug() << "getQueue";
        }
    }
}

void CustomIoReadProcessor::Stop()
{
    m_bTeminated.store(true);
}

void CustomIoReadProcessor::slot_recvDateDisplay(QByteArray str)
{
    emit sig_recvDateDisplay(str, m_typeDataSource);
}

void CustomIoReadProcessor::slot_sendImageInfo(QString netImageWorkEntry)
{
    emit sendImageInfo(netImageWorkEntry, m_typeDataSource);
}


