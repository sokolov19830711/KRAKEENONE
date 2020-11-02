#ifndef IBUTTONFRAME_H
#define IBUTTONFRAME_H

#include <QTimer>

#include "frame.h"

#include "PrimeboxWidgets/OnOffButton.h"
#include "PrimeboxWidgets/SpinBox.h"

class IButtonFrame : public Frame
{
	Q_OBJECT
public:
	IButtonFrame(QSharedPointer<QSettings> settings, McuInData* mcuInData, McuOutData* mcuOutData, QWidget *parent = nullptr);
	virtual ~IButtonFrame();

    virtual void refresh(bool isDeviceConnected);

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

	QTimer _newAdminKeyWritingTimer;
	QTimer _newUserKeyWritingTimer;

};

#endif // IBUTTONFRAME_H
