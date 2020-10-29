#ifndef DUSTFRAME_H
#define DUSTFRAME_H

#include "frame.h"
#include "PrimeboxWidgets/SpinBox.h"
#include "PrimeboxWidgets/SensorInicator.h"
#include "PrimeboxWidgets/ActionsSetupWidget.h"
#include "PrimeboxWidgets/SwitchButtonsWidget.h"

class DustFrame : public Frame
{
	Q_OBJECT
public:
    DustFrame(QSharedPointer<QSettings> settings, McuInData* mcuInData, McuOutData* mcuOutData, QWidget *parent = nullptr);

    virtual ~DustFrame();

    virtual void refresh(bool isDeviceConnected);

signals:

public slots:

private:

    SensorInicator* indicator1_;
    SensorInicator* indicator2_;
    SensorInicator* indicator3_;

    SpinBox* maxValue1_;
    SpinBox* maxValue2_;
    SpinBox* maxValue3_;

	ActionsSetupWidget* _actionsSetupWidget1;
	ActionsSetupWidget* _actionsSetupWidget2;
	ActionsSetupWidget* _actionsSetupWidget3;

    SwitchButtonsWidget* _switchSensorsButtons;
};

#endif // DUSTFRAME_H
