#ifndef BREAKINFRAME_H
#define BREAKINFRAME_H

#include "frame.h"

#include <QLabel>

#include "PrimeboxWidgets/SwitchButtonsWidget.h"
#include "PrimeboxWidgets/OnOffButton.h"

class BreakInFrame : public Frame
{
public:
    BreakInFrame(QSharedPointer<QSettings> settings, McuInData* mcuInData, McuOutData* mcuOutData, QWidget *parent = nullptr);
	virtual ~BreakInFrame();

    virtual void refresh();
    virtual void setControlsEnabled(bool state = true);

private:

	QLabel* sensorName1_;
	QLabel* sensorName2_;
	QLabel* sensorName3_;

    SwitchButtonsWidget* settingsButtons1_;
    SwitchButtonsWidget* settingsButtons2_;
    SwitchButtonsWidget* settingsButtons3_;

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

#endif // BREAKINFRAME_H
