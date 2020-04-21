
#ifndef __TriggerSourceManager_h__
#define __TriggerSourceManager_h__

#include "TriggerSource.h"
#include <vector>
#include <queue>

#include <memory>
using namespace std;

class TriggerSourceManager
{
public:
    TriggerSourceManager();
    void Init(struTriggerSourceConfig config, vector<enumDataSource> dataSources);
    shared_ptr<TriggerSource> getTriggerSource();

private:
    shared_ptr<TriggerSource> m_TriggerSource;

    struTriggerSourceConfig m_config;
};

#endif
