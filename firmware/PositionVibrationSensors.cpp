#include "PositionVibrationSensors.h"
#include "DataManager.h"
#include "Krakeenone_pinout.h"
#include "Beeper.h"

PositionVibrationSensors::PositionVibrationSensors()
{

}

void PositionVibrationSensors::init()
{
	analogReference(EXTERNAL);
}

void PositionVibrationSensors::update()
{
    static int prevX = -999;
    static int prevY = -999;
    static int prevZ = -999;

    const int count = 16;

    int X = 0;
    int Y = 0;
    int Z = 0;

    int vibSensorBuffer[count];

    for (byte i = 0; i < count; i++)
    {
        // переменные акселлерометра
        X += analogRead(X_POS);
        Y += analogRead(Y_POS);
        Z += analogRead(Z_POS);

        // Датчик вибрации
        vibSensorBuffer[i] = analogRead(VIBRO1);
    }

    // Сохраняем средние значения за 16 замеров
    DataManager::outData().positionSensorX = (X / count);
    DataManager::outData().positionSensorY = (Y / count);
    DataManager::outData().positionSensorZ = (Z / count);

	int dX = DataManager::outData().positionSensorX - prevX;
	int dY = DataManager::outData().positionSensorY - prevY;
	int dZ = DataManager::outData().positionSensorZ - prevZ;

    if (prevX != -999)
    {
        int dMax = dX > dY ? dX : dY;
        dMax = dZ > dMax ? dZ : dMax;

        DataManager::outData().vibrationSensor2 = dMax;

        if (dMax > DataManager::config().vibrationMaxValue2 &&
            DataManager::config().vibrationFlags2 & ActionsFlag::soundSignal)
        {
            Beeper::beep();
        }
    }

    prevX = DataManager::outData().positionSensorX;
    prevY = DataManager::outData().positionSensorY;
    prevZ = DataManager::outData().positionSensorZ;

    // Сохраняем максимальное значение из 16 замеров
    DataManager::outData().vibrationSensor1 = getMax(vibSensorBuffer, count) / 4;

    if (DataManager::outData().vibrationSensor1 > DataManager::config().vibrationMaxValue1 &&
        DataManager::config().vibrationFlags1 & ActionsFlag::soundSignal)
    {
        Beeper::beep();
    }
}
