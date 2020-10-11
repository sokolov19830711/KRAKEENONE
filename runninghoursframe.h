#ifndef RUNNINGHOURSFRAME_H
#define RUNNINGHOURSFRAME_H

#include "frame.h"

#include <QLabel>
#include <QPushButton>

class RunningHoursFrame : public Frame
{
	Q_OBJECT
public:
	RunningHoursFrame(QSharedPointer<QSettings> settings, McuInData* mcuInData, McuOutData* mcuOutData, QWidget *parent = nullptr);
	virtual ~RunningHoursFrame();

	virtual void setControlsEnabled(bool state = true);
    virtual void refresh();

signals:

public slots:

private:

	QLabel* sumDeviceTime_;
	QLabel* sumPcTime_;
	QLabel* sessionDeviceTime_;
	QLabel* sessionPcTime_;

	QPushButton* exportLogButton_;

	QLabel* builtInBatteryState_;
	QLabel* externBatteryState_;
};

#endif // RUNNINGHOURSFRAME_H
