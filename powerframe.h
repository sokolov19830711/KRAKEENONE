#ifndef POWERFRAME_H
#define POWERFRAME_H

#include "frame.h"

#include "PrimeboxWidgets/OnOffButton.h"
#include "PrimeboxWidgets/SpinBox.h"
#include "PrimeboxWidgets/SwitchButtonsWidget.h"

class PowerFrame : public Frame
{
public:

    PowerFrame(QSharedPointer<QSettings> settings, McuInData* mcuInData, McuOutData* mcuOutData, QWidget *parent = nullptr);
    virtual ~PowerFrame();

    virtual void refresh(bool isDeviceConnected);

private:

    SwitchButtonsWidget* blockHDDSettingsButtons_;
    SwitchButtonsWidget* resetSettingsButtons_;

    SwitchButtonsWidget* pwswStatePanel_;
	SwitchButtonsWidget* digit1_;
	SwitchButtonsWidget* digit2_;
	SwitchButtonsWidget* digit3_;

    OnOffButton* powerButtonActiveButton_;
    OnOffButton* resetButtonActiveButton_;

    SpinBox* blockingTime_;
    SpinBox* inputPeriod_;

    OnOffButton* notResponseResetButton_;
    SpinBox* notResponseResetTime_;
};

#endif // POWERFRAME_H
