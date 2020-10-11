#include "TemperatureSensors.h"
#include "DataManager.h"
#include "Krakeenone_pinout.h"
#include "Beeper.h"
#include "PcPower.h"
#include "TricolorLED.h"

TemperatureSensors::TemperatureSensors()
{
	
}

void TemperatureSensors::init()
{
	// сигнальный провод датчика
	const int ONE_WIRE_BUS1 = TEMP1;
	const int ONE_WIRE_BUS2 = TEMP2;
	const int ONE_WIRE_BUS3 = TEMP3;

	// создаём объект для работы с библиотекой OneWire
	_oneWire1 = OneWire(ONE_WIRE_BUS1);
	_oneWire2 = OneWire(ONE_WIRE_BUS2);
	_oneWire3 = OneWire(ONE_WIRE_BUS3);

	_temperatureSensor1 = DallasTemperature(&_oneWire1);
	_temperatureSensor2 = DallasTemperature(&_oneWire2);
	_temperatureSensor3 = DallasTemperature(&_oneWire3);

	// начинаем работу с датчиками температуры
	_temperatureSensor1.begin();
	_temperatureSensor2.begin();
	_temperatureSensor3.begin();

	// устанавливаем разрешение датчиков, от 9 до 12 бит
	_temperatureSensor1.setResolution(9);
	_temperatureSensor2.setResolution(9);
	_temperatureSensor3.setResolution(9);

	_temperatureSensor1.getAddress(_temperatureSensorAddr1, 0);
	_temperatureSensor2.getAddress(_temperatureSensorAddr2, 0);
	_temperatureSensor3.getAddress(_temperatureSensorAddr3, 0);
}

void TemperatureSensors::update()
{
	if (_temperatureSensor1.requestTemperaturesByAddress(_temperatureSensorAddr1)) DataManager::outData().temperatureSensor1 = _temperatureSensor1.getTempC(_temperatureSensorAddr1);
	if (_temperatureSensor2.requestTemperaturesByAddress(_temperatureSensorAddr2)) DataManager::outData().temperatureSensor2 = _temperatureSensor2.getTempC(_temperatureSensorAddr2);
	if (_temperatureSensor3.requestTemperaturesByAddress(_temperatureSensorAddr3)) DataManager::outData().temperatureSensor3 = _temperatureSensor3.getTempC(_temperatureSensorAddr3);

	if (DataManager::outData().temperatureSensor1 > DataManager::config().temperatureMaxValue1 &&
		DataManager::config().temperatureFlags1 & ActionsFlag::soundSignal)
	{
		Beeper::beep();
	}

	if (DataManager::outData().temperatureSensor2 > DataManager::config().temperatureMaxValue2 &&
		DataManager::config().temperatureFlags2 & ActionsFlag::soundSignal)
	{
		Beeper::beep();
	}

	if (DataManager::outData().temperatureSensor3 > DataManager::config().temperatureMaxValue3 &&
		DataManager::config().temperatureFlags3 & ActionsFlag::soundSignal)
	{
		Beeper::beep();
	}

}
