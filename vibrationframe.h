#ifndef VIBRATIONFRAME_H
#define VIBRATIONFRAME_H

#include "frame.h"
#include "onoffbutton.h"
#include "sensorinicator.h"
#include "spinbox.h"

class VibrationFrame : public Frame
{
	Q_OBJECT
public:
    explicit VibrationFrame(QSharedPointer<QSettings> settings, McuInData *mcuInData, McuOutData *mcuOutData, QWidget *parent = nullptr);
    virtual ~VibrationFrame();

    virtual void refresh();
    virtual void setControlsEnabled(bool state = true);

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

    OnOffButton* notificationButton1_;
    OnOffButton* soundSignalButton1_;
    OnOffButton* PCShutDownButton1_;

    OnOffButton* notificationButton2_;
    OnOffButton* soundSignalButton2_;
    OnOffButton* PCShutDownButton2_;

    OnOffButton* notificationButton3_;
    OnOffButton* soundSignalButton3_;
    OnOffButton* PCShutDownButton3_;

    OnOffButton* notificationButton4_;
    OnOffButton* soundSignalButton4_;
    OnOffButton* PCShutDownButton4_;
};

#endif // VIBRATIONFRAME_H
