
#include "ICustomIO.h"
#include "DataSource.h"
#include "Helper/EnumTypeConverter.h"


shared_ptr<CustomIO::ICustomIO> DataSource::getCustomIO()
{
    return m_ICustomIO;
}

enumDataSource DataSource::getType() const
{
    return m_type;
}

int DataSource::Init(enumDataSource type, QStringList configData)
{
    m_type = type;

    enumIoType ioType;

    ioType = EnumTypeConverter::ConvertDataSource2Type(type);

    m_objIoFactory = make_unique<IOFactory>();
    m_ICustomIO = m_objIoFactory->create(ioType);
    m_ICustomIO->Init(configData);

    return 0;
}
