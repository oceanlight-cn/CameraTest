
#include "DataSourceManager.h"
#include "DataSource.h"



vector<shared_ptr<DataSource> > DataSourceManager::getDataSources() const
{
    return m_vec_DataSources;
}

void DataSourceManager::Clear()
{
    m_vec_DataSources.clear();
}

void DataSourceManager::AddDataSource(shared_ptr<DataSource>  src)
{
    m_vec_DataSources.push_back(src);
}
