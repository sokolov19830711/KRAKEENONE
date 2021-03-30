#include <Arduino.h>

#include "DustSensors.h"
#include "DataManager.h"
#include "Krakeenone_pinout.h"
#include "Beeper.h"
#include "PcPower.h"

DustSensors::DustSensors()
{

}

void DustSensors::init()
{
    digitalWrite(DUST_LED_INT, HIGH);
}

void DustSensors::update()
{
    // ���������� ������
	if (DataManager::config().dustFlags1 & ActionsFlag::active)
	{
		DataManager::outData().dustSensor1 = analogRead(A3);
		if (DataManager::outData().dustSensor1 > 250) DataManager::outData().dustSensor1 = 250;
		if (DataManager::outData().dustSensor1 > DataManager::config().dustMaxValue1)
		{
			if (DataManager::config().dustFlags1 & ActionsFlag::soundSignal)
			{
				Beeper::beep();
			}

			if (DataManager::config().dustFlags1 & ActionsFlag::PCShutDown)
			{
				PcPower::on();
			}
		}
	}

    // �������� ������ Sharp

	digitalWrite(DUST_LED_SHARP, LOW); // ��� ���������� ������ � �������
	delayMicroseconds(280); //�������, ��� �����

	//float voltsMeasured = analogRead(DUST_RES_SHARP); // ������� ��������
	int voltsMeasured = analogRead(DUST_RES_SHARP); // ������� ��������
	int result = 11;

	if(voltsMeasured == 0)
		result = 11;
	else if (voltsMeasured < 10)
		result = voltsMeasured * 2;
	else if (voltsMeasured < 100)
		result = voltsMeasured / 2;
	else
		result = voltsMeasured / 4;

	delayMicroseconds(40);// ������� ���� �����
	digitalWrite(DUST_LED_SHARP, HIGH); // ���� ������

	if (DataManager::config().dustFlags2 & ActionsFlag::active)
	{
		//DataManager::outData().dustSensor2 = (0.17f * voltsMeasured * (4.096f / 1024.0f) - 0.1f) * 1000.f;
		DataManager::outData().dustSensor2 = result;

		if (DataManager::outData().dustSensor2 > DataManager::config().dustMaxValue2)
		{
			if (DataManager::config().dustFlags2 & ActionsFlag::soundSignal)
			{
				Beeper::beep();
			}

			if (DataManager::config().dustFlags2 & ActionsFlag::PCShutDown)
			{
				PcPower::on();
			}
		}
	}
}
