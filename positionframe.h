#ifndef POSITIONFRAME_H
#define POSITIONFRAME_H

#include "frame.h"
#include "PrimeboxWidgets/SpinBox.h"
#include "PrimeboxWidgets/SensorInicator.h"
#include "PrimeboxWidgets/ActionsSetupWidget.h"
#include "PrimeboxWidgets/SwitchButtonsWidget.h"

#include <QPushButton>

class PositionFrame : public Frame
{
	Q_OBJECT

public:

    explicit PositionFrame(QSharedPointer<QSettings> settings, McuInData* mcuInData, McuOutData* mcuOutData, QWidget *parent = nullptr);
    virtual ~PositionFrame();

    virtual void refresh(bool isDeviceConnected);

signals:

public slots:

private:

    SensorInicator* xValue_;
    SensorInicator* yValue_;
    SensorInicator* zValue_;

    QPushButton* saveStartingPositionButton_;
    QPushButton* resetStartingPositionButton_;
    QPushButton* resetlimitsButton_;

    SpinBox* xLimit_;
    SpinBox* yLimit_;
    SpinBox* zLimit_;

    ActionsSetupWidget* _actionsSetupWidget;
    SwitchButtonsWidget* _switchSensorsButtons;

};

#endif // POSITIONFRAME_H
