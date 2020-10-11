#ifndef POSITIONFRAME_H
#define POSITIONFRAME_H

#include "frame.h"
#include "spinbox.h"
#include "onoffbutton.h"
#include "sensorinicator.h"

#include <QPushButton>

class PositionFrame : public Frame
{
	Q_OBJECT

public:

    explicit PositionFrame(QSharedPointer<QSettings> settings, McuInData* mcuInData, McuOutData* mcuOutData, QWidget *parent = nullptr);
    virtual ~PositionFrame();

    virtual void refresh();
    virtual void setControlsEnabled(bool state = true);

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

    OnOffButton* notificationButton_;
    OnOffButton* soundSignalButton_;
    OnOffButton* PCShutDownButton_;
};

#endif // POSITIONFRAME_H
