#ifndef CAMERATEST_H
#define CAMERATEST_H
#include <QObject>

class CameraTest: public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isEthernetSet READ EthernetSet WRITE setEthernetSet)
    Q_PROPERTY(bool isSerialportSet READ SerialportSet WRITE setSerialportSet)

public:
    CameraTest();

    bool EthernetSet() const;
    bool SerialportSet() const;
    void StartTest();

public slots:
    void setEthernetSet(bool isEthernetSet);
    void setSerialportSet(bool isSerialportSet);

private:
    bool m_isEthernetSet, m_isSerialportSet;
};

#endif // CAMERATEST_H
