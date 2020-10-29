#ifndef MOISTUREFRAME_H
#define MOISTUREFRAME_H

#include "frame.h"
#include "PrimeboxWidgets/SpinBox.h"
#include "PrimeboxWidgets/SensorInicator.h"
#include "PrimeboxWidgets/ActionsSetupWidget.h"
#include "PrimeboxWidgets/SwitchButtonsWidget.h"

class MoistureFrame : public Frame
{
	Q_OBJECT
public:
    MoistureFrame(QSharedPointer<QSettings> settings, McuInData* mcuInData, McuOutData* mcuOutData, QWidget *parent = nullptr);
    virtual ~MoistureFrame();

    virtual void refresh(bool isDeviceConnected);

signals:

public slots:

private:

    SensorInicator* indicator_;

    SpinBox* minValue_;
    SpinBox* maxValue_;

    ActionsSetupWidget* _actionsSetupWidget;
    SwitchButtonsWidget* _switchSensorsButtons;
};

#endif // MOISTUREFRAME_H
