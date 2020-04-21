
#ifndef __DataSource_h__
#define __DataSource_h__

#include "globaldef.h"
#include "ICustomIO.h"
#include <memory>
#include "IOFactory.h"

using namespace std;

class DataSource
{
public:
    shared_ptr<CustomIO::ICustomIO> getCustomIO();

    enumDataSource getType() const;

    int Init(enumDataSource type, QStringList configData);

private:
    shared_ptr<CustomIO::ICustomIO> m_ICustomIO;
    unique_ptr<IOFactory> m_objIoFactory;
    enumDataSource m_type;
};


#endif
