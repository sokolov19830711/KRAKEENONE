#include <GyverTimers.h>

#include "DataManager.h"
#include "InternalMemoryManager.h"
#include "TemperatureSensors.h"
#include "MoistureSensors.h"
#include "DustSensors.h"
#include "PositionVibrationSensors.h"
#include "BreakInSensors.h"
#include "PowerButtonWatcher.h"

#include "Beeper.h"
#include "PcPower.h"
#include "TricolorLED.h"

#include "Krakeenone_pinout.h"

//IButton
const int IBUTTON = 26;

static InternalMemoryManager internalMemoryManager;
static TemperatureSensors temperatureSensors;
static MoistureSensors moistureSensors;
static DustSensors dustSensors;
static PositionVibrationSensors positionVibrationSensors;
static BreakInSensors breakInSensors;
static PowerButtonWatcher powerButtonWatcher;

static int loopsCounter = 0; // счетчик кол-ва вызовов функции loop()
const int LOOPS_COUNT = 100; // кол-во циклов, через которое мы снимаем показания с "тяжелых" датчиков.
const int TIMER_PERIOD = 20000; // в микросекундах

void setup()
{
    DataManager::init();
    Beeper::init(BEEPER, TIMER_PERIOD, 100);
    PcPower::init(PC_POWER, TIMER_PERIOD, 20);
    TricolorLED::init(RED, TIMER_PERIOD, 200);

    internalMemoryManager.initConfig();

    Timer5.setPeriod(TIMER_PERIOD); // Устанавливаем период таймера 20000 мкс -> 50 гц
    Timer5.enableISR(CHANNEL_A); // Или просто.enableISR(), запускаем прерывание на канале А таймера

    Serial.begin(19200);

    temperatureSensors.init();
    moistureSensors.init();
    dustSensors.init();
    positionVibrationSensors.init();
    powerButtonWatcher.updateConfig();
}

void loop()
{
  // Сохраняем текущее время с последнего запуска устройства
    DataManager::outData().sessionRunningTime = millis() / 1000;

    if(loopsCounter > LOOPS_COUNT)
    {
      loopsCounter = 0;
      
      // Влажность
      moistureSensors.update();

      // Температура
      temperatureSensors.update();

      // Датчик пыли
      dustSensors.update();

      // Датчики вскрытия
      breakInSensors.update();
    }

    else
    {
        loopsCounter++;

        positionVibrationSensors.update();

        Serial.write(reinterpret_cast<uint8_t*>(&DataManager::outData()), sizeof(McuOutData)); // Отсылаем структуру с текущим состоянием устройства

        if(Serial.peek() == START_MARKER1)
        {
            static McuInData inData;
            if (Serial.readBytes(reinterpret_cast<uint8_t*>(&inData), sizeof(McuInData)) == sizeof(McuInData)) // Принимаем структуру с заданиями от программы на ПК
            {
                if ((inData.startMarker1 == START_MARKER1) && (inData.startMarker2 == START_MARKER2))
                {
                    const char* tmpPtr1 = reinterpret_cast<const char*>(&DataManager::config());
                    const char* tmpPtr2 = reinterpret_cast<const char*>(&inData);
                    bool needToUpdate = false;

                    for (size_t i = 0; i < sizeof(McuInData); i++)
                    {
                        if (tmpPtr1[i] != tmpPtr2[i])
                        {
                            needToUpdate = true;
                            break;
                        }
                    }

                    if (needToUpdate)
                    {
                        DataManager::config() = inData;
						internalMemoryManager.saveConfig();
                        powerButtonWatcher.updateConfig();
                    }
                }
            }
        }
    }
}

// Прерывание А таймера 5
ISR(TIMER5_A)
{
    Beeper::update();
    PcPower::update();
    TricolorLED::update();
    powerButtonWatcher.update(TIMER_PERIOD / 1000);
}
