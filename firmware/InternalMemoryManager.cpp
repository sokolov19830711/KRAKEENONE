#include "InternalMemoryManager.h"

#include <string.h>
#include <Arduino.h>

#include "DataManager.h"
#include "Beeper.h"

InternalMemoryManager::InternalMemoryManager()
{

}

void InternalMemoryManager::initConfig()
{
    if (eeprom_read_byte(0) == 123)
    {
        eeprom_read_block((void*)(&DataManager::config()), 1, sizeof(McuInData));
    }
    else
    {
        eeprom_write_byte(0, 123);
        saveConfig();
    }
}

void InternalMemoryManager::saveConfig()
{
    Beeper::beep();
    eeprom_write_block((void*)(&DataManager::config()), 1, sizeof(McuInData));
}
