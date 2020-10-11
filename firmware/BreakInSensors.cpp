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
	if (digitalRead(TERMINAL_SWITCH1) == ((DataManager::config().breakInSensorsStates & 0x1)))
	{
		if (DataManager::config().breakInFlags1 & ActionsFlag::soundSignal)
		{
			Beeper::beep();
		}
	}

	if (digitalRead(TERMINAL_SWITCH2) == ((DataManager::config().breakInSensorsStates & 0x2)))
	{
		if (DataManager::config().breakInFlags2 & ActionsFlag::soundSignal)
		{
			Beeper::beep();
		}
	}

	// Встроенный датчик вскрытия

	if (digitalRead(BREAK_IN_SENSOR_INT) == ((DataManager::config().breakInSensorsStates & 0x4)))
	{
		if (DataManager::config().breakInFlags3 & ActionsFlag::soundSignal)
		{
			Beeper::beep();
		}
	}



}

