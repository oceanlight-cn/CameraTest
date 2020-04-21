
#ifndef __TriggerSource_h__
#define __TriggerSource_h__
#include "ICustomIO.h"
#include "globaldef.h"

class TriggerSource
{
public:
    enumTriggerSource getType() const;

    void setType(const enumTriggerSource &type);

private:
    enumTriggerSource m_type;
};


#endif
