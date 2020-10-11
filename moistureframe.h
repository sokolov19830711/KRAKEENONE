#ifndef MOISTUREFRAME_H
#define MOISTUREFRAME_H

#include "frame.h"
#include "PrimeboxWidgets/OnOffButton.h"
#include "PrimeboxWidgets/SpinBox.h"
#include "PrimeboxWidgets/SensorInicator.h"

#include <QSpinBox>

class MoistureFrame : public Frame
{
	Q_OBJECT
public:
    MoistureFrame(QSharedPointer<QSettings> settings, McuInData* mcuInData, McuOutData* mcuOutData, QWidget *parent = nullptr);
    virtual ~MoistureFrame();

    virtual void refresh();
    virtual void setControlsEnabled(bool state = true);

signals:

public slots:

private:

    SensorInicator* indicator_;

    SpinBox* minValue_;
    SpinBox* maxValue_;

    OnOffButton* notificationButton_;
    OnOffButton* soundSignalButton_;
    OnOffButton* PCShutDownButton_;
};

#endif // MOISTUREFRAME_H
