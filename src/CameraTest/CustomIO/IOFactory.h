
#ifndef __IOFactory_h__
#define __IOFactory_h__

#include "ICustomIO.h"
#include <memory>

using namespace std;

class IOFactory
{
    public:
        unique_ptr<CustomIO::ICustomIO>  create(CustomIO::enumIoType io_type);

    private:
        unique_ptr<CustomIO::ICustomIO> p_objIo;
};

#endif
