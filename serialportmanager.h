#ifndef SERIALPORTMANAGER_H
#define SERIALPORTMANAGER_H

#include <QObject>
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QTimer>

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
    void deviceConnected(bool state);
    void noConnection();

public slots:

     void refresh();
     void setPort(const QString& name);

private:
    const int _connectionWaitingTime = 10000; // Сколько ждем, прежде чем шлем сигнал об отсутствии связи с устройством (мс)
    QSerialPort port_;
    McuInData* mcuInData_;
    McuOutData* mcuOutData_;
    QTimer* _noConnectionTimer;
};

#endif // SERIALPORTMANAGER_H
