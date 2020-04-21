#ifndef READPARSER_H
#define READPARSER_H
#include "globaldef.h"

#include <QString>

class ReadParser
{
public:
    ReadParser();

    int ParseData(QByteArray data, struPacketData& packet);
};

#endif // READPARSER_H
