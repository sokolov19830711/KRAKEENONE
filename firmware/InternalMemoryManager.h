#pragma once

#include <avr/eeprom.h>
#include "dataStructures.h"

class InternalMemoryManager
{
public:
	InternalMemoryManager();
	void initConfig();
	void saveConfig();
};

