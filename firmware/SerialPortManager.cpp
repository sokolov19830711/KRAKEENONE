#include "SerialPortManager.h"

#include <Arduino.h>

SerialPortManager::SerialPortManager()
{

}

void SerialPortManager::init(int baudRate)
{
	Serial.begin(baudRate);
}

void SerialPortManager::update()
{

}
