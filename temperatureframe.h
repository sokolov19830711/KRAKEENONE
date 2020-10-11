#ifndef TEMPERATUREFRAME_H
#define TEMPERATUREFRAME_H

#include "frame.h"

#include <QLabel>
#include "PrimeboxWidgets/SpinBox.h"
#include "PrimeboxWidgets/OnOffButton.h"
#include "PrimeboxWidgets/SensorInicator.h"

class TemperatureFrame : public Frame
{
	Q_OBJECT
public:
    explicit TemperatureFrame(QSharedPointer<QSettings> settings, McuInData* mcuInData, McuOutData* mcuOutData, QWidget *parent = nullptr);
    virtual ~TemperatureFrame();

    virtual void refresh();
    virtual void setControlsEnabled(bool state = true);

signals:

public slots:

private:

    QLabel* sensorName1_;
    QLabel* sensorName2_;
    QLabel* sensorName3_;

    SensorInicator* indicator1_;
    SensorInicator* indicator2_;
    SensorInicator* indicator3_;

    SpinBox* minValue1_;
    SpinBox* maxValue1_;

    SpinBox* minValue2_;
    SpinBox* maxValue2_;

    SpinBox* minValue3_;
    SpinBox* maxValue3_;

    OnOffButton* notificationButton1_;
    OnOffButton* soundSignalButton1_;
    OnOffButton* PCShutDownButton1_;

    OnOffButton* notificationButton2_;
    OnOffButton* soundSignalButton2_;
    OnOffButton* PCShutDownButton2_;

    OnOffButton* notificationButton3_;
    OnOffButton* soundSignalButton3_;
    OnOffButton* PCShutDownButton3_;
};

#endif // TEMPERATUREFRAME_H
