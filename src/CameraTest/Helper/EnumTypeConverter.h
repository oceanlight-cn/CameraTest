#ifndef ENUMTYPECONVERTER_H
#define ENUMTYPECONVERTER_H
#include "globaldef.h"
#include "CustomIO/ICustomIO.h"

using namespace CustomIO;

class EnumTypeConverter
{
public:
    EnumTypeConverter();

    static enumDataSource ConvertType2DataSource(enumIoType type);
    static enumIoType ConvertDataSource2Type(enumDataSource src);
};

#endif // ENUMTYPECONVERTER_H
