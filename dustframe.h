#ifndef DUSTFRAME_H
#define DUSTFRAME_H

#include "frame.h"
#include "spinbox.h"
#include "onoffbutton.h"
#include "sensorinicator.h"

class DustFrame : public Frame
{
	Q_OBJECT
public:
    DustFrame(QSharedPointer<QSettings> settings, McuInData* mcuInData, McuOutData* mcuOutData, QWidget *parent = nullptr);

    virtual ~DustFrame();

    virtual void refresh();
    virtual void setControlsEnabled(bool state = true);

signals:

public slots:

private:

    SensorInicator* indicator1_;
    SensorInicator* indicator2_;
    SensorInicator* indicator3_;

    SpinBox* maxValue1_;
    SpinBox* maxValue2_;
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

#endif // DUSTFRAME_H
