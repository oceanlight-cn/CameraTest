#ifndef READIMAGEMODULE_H
#define READIMAGEMODULE_H

#include <QObject>

class ReadImageModule : public QObject
{
    Q_OBJECT

public:
    ReadImageModule();

    void setTemplateStr(QString &val) { m_TemplateStr = val; }
    QString& getTemplateStr() { return m_TemplateStr; }
    void setCenterStr(QString &val) { m_CenterStr = val; }
    QString& getCenterStr() { return m_CenterStr; }

    void setCoordinateX(QString &val) { m_CoordinateX = val; }
    QString& getCoordinateX() { return m_CoordinateX; }
    void setCoordinateY(QString &val) { m_CoordinateY = val; }
    QString& getCoordinateY() { return m_CoordinateY; }

    void ProcessData(QByteArray data);

private:
    QString m_TemplateStr;
    QString m_CenterStr;

    QString m_CoordinateX;
    QString m_CoordinateY;

signals:
      void recvDateDisplay(QByteArray str);
      void sendImageInfo(QString netImageWorkEntry);
      void sendImageOKCount(int NetOKCount);
};

#endif // READIMAGEMODULE_H
