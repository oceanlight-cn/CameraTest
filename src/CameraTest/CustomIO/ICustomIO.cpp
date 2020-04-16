#include <exception>
using namespace std;

#include "ICustomIO.h"

namespace CustomIO
{
    bool ICustomIO::getIsEnable() const
    {
        return m_isEnable;
    }

    void ICustomIO::setIsEnable(bool isEnable)
    {
        m_isEnable = isEnable;
    }

    ICustomIO::~ICustomIO()
    {

    }

    enumIoType ICustomIO::getIo_type() const
    {
        return m_io_type;
    }

    void ICustomIO::setIo_type(const enumIoType &io_type)
    {
        m_io_type = io_type;
    }
}

