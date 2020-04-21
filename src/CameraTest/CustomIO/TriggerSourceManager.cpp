
#include "TriggerSourceManager.h"
#include "TriggerSource.h"


TriggerSourceManager::TriggerSourceManager()
{
    m_TriggerSource = make_shared<TriggerSource>();
}

void TriggerSourceManager::Init(struTriggerSourceConfig config, vector<enumDataSource> dataSources)
{
    m_TriggerSource->setType(config.triggerSource);
}

shared_ptr<TriggerSource> TriggerSourceManager::getTriggerSource()
{
    shared_ptr<TriggerSource> pTriggerSource;

    switch (m_TriggerSource->getType()) {
    case enumTriggerSource::ETHERNET:
    case enumTriggerSource::SERIAL_PORT:
        pTriggerSource = m_TriggerSource;
        break;

    default:
        break;
    }
    return pTriggerSource;
}


