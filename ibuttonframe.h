#ifndef IBUTTONFRAME_H
#define IBUTTONFRAME_H

#include "frame.h"

#include "PrimeboxWidgets/OnOffButton.h"
#include "PrimeboxWidgets/SpinBox.h"

class IButtonFrame : public Frame
{
	Q_OBJECT
public:
	IButtonFrame(QSharedPointer<QSettings> settings, McuInData* mcuInData, McuOutData* mcuOutData, QWidget *parent = nullptr);
	virtual ~IButtonFrame();

    virtual void refresh();
	virtual void setControlsEnabled(bool state = true);

signals:

public slots:

private:

	OnOffButton* turnOnButton_;
	OnOffButton* lockPWRButtonButton_;
	OnOffButton* resetButton_;
	OnOffButton* powerOffButton_;

	SpinBox* invalidKeyUsageCountToReset_;
	SpinBox* invalidKeyUsageCountToTurnOff_;

	QPushButton* setupNewUserKeyButton_;
	QPushButton* setupNewAdminKeyButton_;

};

#endif // IBUTTONFRAME_H
