#include "BreakInSensors.h"

#include <Arduino.h>
#include "DataManager.h"
#include "Krakeenone_pinout.h"
#include "Beeper.h"

BreakInSensors::BreakInSensors()
{

}

void BreakInSensors::init()
{

}

void BreakInSensors::update()
{
	// Концевые выключатели
	int switch1 = digitalRead(TERMINAL_SWITCH1);
	DataManager::outData().breakInSensor1 = switch1;

	if (switch1 == ((DataManager::config().breakInSensorsStates & 0x1)))
	{
		if (DataManager::config().breakInFlags1 & ActionsFlag::soundSignal)
		{
			Beeper::beep();
		}
	}

	int switch2 = digitalRead(TERMINAL_SWITCH2);
	DataManager::outData().breakInSensor2 = switch2;

	if (switch2 == ((DataManager::config().breakInSensorsStates & 0x2)))
	{
		if (DataManager::config().breakInFlags2 & ActionsFlag::soundSignal)
		{
			Beeper::beep();
		}
	}

	// Встроенный датчик вскрытия

	int sensor = digitalRead(BREAK_IN_SENSOR_INT);
	DataManager::outData().breakInSensor3 = sensor;

	if (sensor == ((DataManager::config().breakInSensorsStates & 0x4)))
	{
		if (DataManager::config().breakInFlags3 & ActionsFlag::soundSignal)
		{
			Beeper::beep();
		}
	}



}

