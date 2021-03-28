#include "serialportmanager.h"
#include "firmware/dataStructures.h"

#include <QDebug>

SerialPortManager::SerialPortManager(QObject *parent) : QObject(parent)
{
	_noConnectionTimer = new QTimer(this);
	connect(_noConnectionTimer, SIGNAL(timeout()), this, SIGNAL(noConnection()));
	_noConnectionTimer->start(_connectionWaitingTime);
}

SerialPortManager::SerialPortManager(const QSerialPortInfo &portInfo, McuInData* mcuInData, McuOutData* mcuOutData, QObject *parent) :
    QObject(parent),
    mcuInData_(mcuInData),
    mcuOutData_(mcuOutData)
{
    port_.setPort(portInfo);
    port_.setBaudRate(19200);
    port_.open(QIODevice::ReadWrite);
    connect(&port_, SIGNAL(readyRead()), this, SLOT(refresh()));

    _noConnectionTimer = new QTimer(this);
	connect(_noConnectionTimer, SIGNAL(timeout()), this, SIGNAL(noConnection()));
    _noConnectionTimer->start(_connectionWaitingTime);
}

SerialPortManager::~SerialPortManager()
{

}

QString SerialPortManager::getPortName() const
{
    return port_.portName();
}

bool SerialPortManager::connectedToPort() const
{
    return port_.isOpen();
}

void SerialPortManager::refresh()
{
    static int isSync = 0;
    static int counter = 0;
    static QByteArray data;

    if (isSync != 2)
    {
        data.append(port_.read(sizeof(McuOutData)));
        if(data.size() >= sizeof(McuOutData))
		{
			int marker1Pos = data.indexOf(START_MARKER1);
			int marker2Pos = data.indexOf(START_MARKER2);
			if ((marker2Pos - marker1Pos) == 1)
			{
				data = data.mid(marker1Pos);
                if(data.at(9) == CONTROL_MARKER)
				{
					isSync++;
                    if(isSync == 2)
					{
                        emit deviceConnected(true);
                    }
				}
			}

            else if (data.size() > 1000)
            {
                data.clear();
            }
		}
    }

    else
    {
        //qDebug() << "Size of recieved bytearray:" << data.size() << "bytes; content of array:" << data;

        if (data.size() >= sizeof(*mcuOutData_))
        {
            memcpy(mcuOutData_, data.data(), sizeof(*mcuOutData_));
            data = data.mid(sizeof(*mcuOutData_));
        }

		data.append(port_.read(sizeof(*mcuOutData_)));

        _noConnectionTimer->start(_connectionWaitingTime);
    }

    if (counter < 100)
    {
        counter++;
    }
    else // ќтсылаем настройки контроллеру на каждый 100 цикл (~раз в 1 сек)
    {
        counter = 0;
        port_.write(reinterpret_cast<const char*>(mcuInData_), sizeof(*mcuInData_));
        port_.waitForBytesWritten(10);
    }
}

void SerialPortManager::setPort(const QString &name)
{
    auto ports = QSerialPortInfo::availablePorts();
    for (auto & i : ports)
    {
        if(i.portName() == name)
        {
            port_.close();
            port_.setPort(i);
            port_.setBaudRate(19200);
            port_.open(QIODevice::ReadWrite);
            break;
        }
    }
}
