
#ifndef __DataSourceManager_h__
#define __DataSourceManager_h__

#include "DataSource.h"
#include <vector>

#include <memory>
using namespace std;

class DataSourceManager
{
public:
    vector<shared_ptr<DataSource>> getDataSources() const;
    void Clear();
    void AddDataSource(shared_ptr<DataSource> src);

private:
    vector<shared_ptr<DataSource>> m_vec_DataSources;
};

#endif
