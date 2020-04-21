#include "CameraTest.h"
#include <QDebug>

CameraTest::CameraTest()
{

}

bool CameraTest::EthernetSet() const
{
    return m_isEthernetSet;
}

bool CameraTest::SerialportSet() const
{
    return m_isSerialportSet;
}

void CameraTest::StartTest()
{

}

void CameraTest::setEthernetSet(bool isEthernetSet)
{
    m_isEthernetSet = isEthernetSet;
}

void CameraTest::setSerialportSet(bool isSerialportSet)
{
    m_isSerialportSet = isSerialportSet;
}


