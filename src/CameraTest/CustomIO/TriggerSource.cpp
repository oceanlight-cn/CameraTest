
#include "TriggerSource.h"
#include "ICustomIO.h"
#include "TriggerSourceManager.h"


enumTriggerSource TriggerSource::getType() const
{
    return m_type;
}

void TriggerSource::setType(const enumTriggerSource &type)
{
    m_type = type;
}


