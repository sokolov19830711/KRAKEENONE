#ifndef BREAKINFRAME_H
#define BREAKINFRAME_H

#include "frame.h"

#include <QLabel>

#include "PrimeboxWidgets/SwitchButtonsWidget.h"
#include "PrimeboxWidgets/ActionsSetupWidget.h"

class BreakInFrame : public Frame
{
public:
    BreakInFrame(QSharedPointer<QSettings> settings, McuInData* mcuInData, McuOutData* mcuOutData, QWidget *parent = nullptr);
	virtual ~BreakInFrame();

    virtual void refresh(bool isDeviceConnected);

private:

	QLabel* sensorName1_;
	QLabel* sensorName2_;
	QLabel* sensorName3_;

    SwitchButtonsWidget* settingsButtons1_;
    SwitchButtonsWidget* settingsButtons2_;
    SwitchButtonsWidget* settingsButtons3_;

	ActionsSetupWidget* _actionsSetupWidget1;
	ActionsSetupWidget* _actionsSetupWidget2;
	ActionsSetupWidget* _actionsSetupWidget3;

	SwitchButtonsWidget* _switchSensorsButtons;
};

#endif // BREAKINFRAME_H
