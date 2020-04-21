
#include "NetIo.h"
#include "SerialPortIO.h"

#include "IOFactory.h"


unique_ptr<CustomIO::ICustomIO> IOFactory::create(CustomIO::enumIoType io_type)
{
    p_objIo = nullptr;

    switch (io_type) {
    case CustomIO::enumIoType::ETHERNET:
        p_objIo = make_unique<CustomIO::NetIO>();
        p_objIo->setIo_type(CustomIO::enumIoType::ETHERNET);

        break;
    case CustomIO::enumIoType::SERIAL_PORT:
        p_objIo = make_unique<CustomIO::SerialPortIO>();
        p_objIo->setIo_type(CustomIO::enumIoType::SERIAL_PORT);

        break;

    default:
        break;
    }

    return std::move(p_objIo);
}
