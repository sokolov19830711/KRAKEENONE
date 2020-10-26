#ifndef VIBRATIONFRAME_H
#define VIBRATIONFRAME_H

#include "frame.h"
#include "PrimeboxWidgets/SpinBox.h"
#include "PrimeboxWidgets/OnOffButton.h"
#include "PrimeboxWidgets/SensorInicator.h"
#include "PrimeboxWidgets/ActionsSetupWidget.h"

class VibrationFrame : public Frame
{
	Q_OBJECT
public:
    explicit VibrationFrame(QSharedPointer<QSettings> settings, McuInData *mcuInData, McuOutData *mcuOutData, QWidget *parent = nullptr);
    virtual ~VibrationFrame();

    virtual void refresh(bool isDeviceConnected);

signals:

public slots:

private:

    SensorInicator* indicator1_;
    SensorInicator* indicator2_;
    SensorInicator* indicator3_;
    SensorInicator* indicator4_;

    SpinBox* maxValue1_;
    SpinBox* maxValue2_;
    SpinBox* maxValue3_;
    SpinBox* maxValue4_;

    ActionsSetupWidget* _actionsSetupWidget1;
    ActionsSetupWidget* _actionsSetupWidget2;
    ActionsSetupWidget* _actionsSetupWidget3;
    ActionsSetupWidget* _actionsSetupWidget4;

};

#endif // VIBRATIONFRAME_H
