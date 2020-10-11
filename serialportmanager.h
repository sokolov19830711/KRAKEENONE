#ifndef SERIALPORTMANAGER_H
#define SERIALPORTMANAGER_H

#include <QObject>
#include <QSerialPortInfo>
#include <QSerialPort>

#include "firmware/dataStructures.h"

class SerialPortManager : public QObject
{
    Q_OBJECT

public:

    explicit SerialPortManager(QObject *parent = nullptr);
    SerialPortManager(const QSerialPortInfo& portInfo, McuInData* mcuInData, McuOutData* mcuOutData, QObject *parent = nullptr);
    virtual ~SerialPortManager();

    QString getPortName() const;
    bool connectedToPort() const;

signals:

public slots:

     void refresh();
     void setPort(const QString& name);

private:

    QSerialPort port_;
    McuInData* mcuInData_;
    McuOutData* mcuOutData_;
};

#endif // SERIALPORTMANAGER_H
