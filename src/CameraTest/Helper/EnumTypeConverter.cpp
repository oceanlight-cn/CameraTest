#include "EnumTypeConverter.h"

EnumTypeConverter::EnumTypeConverter()
{

}

enumDataSource EnumTypeConverter::ConvertType2DataSource(enumIoType type)
{
    enumDataSource src;
    switch (type) {
    case enumIoType::ETHERNET:
        src = enumDataSource::ETHERNET;
        break;
    case enumIoType::SERIAL_PORT:
        src = enumDataSource::SERIAL_PORT;
        break;
    default:
        break;
    }

    return src;
}

enumIoType EnumTypeConverter::ConvertDataSource2Type(enumDataSource src)
{
    enumIoType type;
    switch (src) {
    case enumDataSource::ETHERNET:
        type = enumIoType::ETHERNET;
        break;
    case enumDataSource::SERIAL_PORT:
        type = enumIoType::SERIAL_PORT;
        break;
    default:
        break;
    }

    return type;
}
