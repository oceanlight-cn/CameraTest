#ifndef CAMERATEST_H
#define CAMERATEST_H
#include <QObject>
#include <QTimer>
#include <memory>
#include <QDateTime>
#include "TestModule/TestProcessManager.h"

using namespace std;
class CameraTest: public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isEthernetSet READ EthernetSet WRITE setEthernetSet)
    Q_PROPERTY(bool isSerialportSet READ SerialportSet WRITE setSerialportSet)
    Q_PROPERTY(QString ip READ getIp WRITE setIp)
    Q_PROPERTY(int port READ getPort WRITE setPort)
    Q_PROPERTY(int duration READ getDuration WRITE setDuration)
    Q_PROPERTY(QString comport READ getComport WRITE setComport)
    Q_PROPERTY(int baudrate READ getBaudrate WRITE setBaudrate)
    Q_PROPERTY(QString parity READ getParity WRITE setParity)
    Q_PROPERTY(int databits READ getDatabits WRITE setDatabits)
    Q_PROPERTY(QString stopbits READ getStopbits WRITE setStopbits)

public:
    CameraTest();

    bool EthernetSet() const;
    bool SerialportSet() const;
    Q_INVOKABLE void StartTest();
    Q_INVOKABLE void StopTest();
    int getPort() const;
    QString getIp() const;

    int getDuration() const;
    void setDuration(int duration);

    QString getComport() const;
    void setComport(const QString &comport);

    int getBaudrate() const;
    void setBaudrate(int baudrate);

    QString getParity() const;
    void setParity(const QString &parity);

    int getDatabits() const;
    void setDatabits(int databits);

    QString getStopbits() const;
    void setStopbits(const QString &stopbits);

public slots:
    void setEthernetSet(bool isEthernetSet);
    void setSerialportSet(bool isSerialportSet);
    void setPort(int port);
    void setIp(QString ip);
    void updateTime();
    void RecvDateDisplay(QByteArray str, enumDataSource src);
    void RecvImageInfo(QString netImageWorkEntry, enumDataSource src);

signals:
    void increaseFailCount();
    void sendCoordinate(QString pos);

private:
    void InitConfigs();
    void SetSerialConfig(struSerialData& data);

    bool m_isEthernetSet, m_isSerialportSet;
    QString m_ip;
    int m_port;
    int m_duration;
    QString m_comport;
    int m_baudrate;
    QString m_parity;
    int m_databits;
    QString m_stopbits;

    unique_ptr<QTimer> m_timer;
    QDateTime m_reachDateTime;
    unique_ptr<TestProcessManager> m_TestProcessManager;

    struDataSourceConfig m_DataSourceConfig;
    struTriggerSourceConfig m_TriggerSourceConfig;
    struTestConfig m_testConfig;
};

#endif // CAMERATEST_H
