#include "mainframe.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGridLayout>

MainFrame::MainFrame(QSharedPointer<QSettings> settings, McuInData *mcuInData, McuOutData *mcuOutData, QWidget *parent) : Frame(settings, mcuInData, mcuOutData, parent)
{ 
    QGridLayout* mainLayout = new QGridLayout;

    addMainLayout(mainLayout);

    powerStatusButton_ = new OnOffButton(this);
    powerStatusButton_->setEnabled(false);
    powerStatusButton_->setChecked(true);

    mainLayout->addWidget(new QLabel("СТАТУС ПИТАНИЯ УСТРОЙСТВА"), 0, 0, Qt::AlignRight);
    mainLayout->addWidget(powerStatusButton_, 0, 1);

    //---

    activityStatusButton_ = new OnOffButton(this);
    activityStatusButton_->setEnabled(false);
    activityStatusButton_->setChecked(true);

    mainLayout->addWidget(new QLabel("АКТИВНО | BYPASS"), 1, 0, Qt::AlignRight);
    mainLayout->addWidget(activityStatusButton_, 1, 1);

    //---

    ledIndicatorButton1_ = new OnOffButton(this);
    ledIndicatorButton1_->setEnabled(false);
    ledIndicatorButton1_->setChecked(true);

    ledIndicatorButton2_ = new OnOffButton(this);
    ledIndicatorButton2_->setEnabled(false);
    ledIndicatorButton2_->setChecked(false);

    ledIndicatorLabel_ = new QLabel(this);
    ledIndicatorLabel_->setText("встроенный | выносной");
    ledIndicatorLabel_->setStyleSheet("color:#ffc000");

    QHBoxLayout* ledIndicatorLayout = new QHBoxLayout;
    ledIndicatorLayout->setMargin(0);
    QWidget* ledIndicatorWidget = new QWidget;
    ledIndicatorWidget->setLayout(ledIndicatorLayout);
    ledIndicatorLayout->addWidget(ledIndicatorButton1_);
    ledIndicatorLayout->addWidget(ledIndicatorButton2_);
    ledIndicatorLayout->addWidget(ledIndicatorLabel_);

    mainLayout->addWidget(new QLabel("СВЕТОДИОД"), 2, 0, Qt::AlignRight);
    mainLayout->addWidget(ledIndicatorWidget, 2, 1);

    //---

    vibrationButton1_ = new OnOffButton(this);
    vibrationButton1_->setEnabled(false);
    vibrationButton1_->setChecked(true);

    vibrationButton2_ = new OnOffButton(this);
    vibrationButton2_->setEnabled(false);
    vibrationButton2_->setChecked(true);

    vibrationButton3_ = new OnOffButton(this);
    vibrationButton3_->setEnabled(false);
    vibrationButton3_->setChecked(false);

    vibrationButton4_ = new OnOffButton(this);
    vibrationButton4_->setEnabled(false);
    vibrationButton4_->setChecked(false);

    vibrationLabel_ = new QLabel(this);
    vibrationLabel_->setText("датчики 1|2|3|4");
    vibrationLabel_->setStyleSheet("color:#ffc000");

    QHBoxLayout* vibrationLayout = new QHBoxLayout;
    vibrationLayout->setMargin(0);
    QWidget* vibrationWidget = new QWidget;
    vibrationWidget->setLayout(vibrationLayout);
    vibrationLayout->addWidget(vibrationButton1_);
    vibrationLayout->addWidget(vibrationButton2_);
    vibrationLayout->addWidget(vibrationButton3_);
    vibrationLayout->addWidget(vibrationButton4_);
    vibrationLayout->addWidget(vibrationLabel_);

    mainLayout->addWidget(new QLabel("ВИБРАЦИЯ | УДАР"), 3, 0, Qt::AlignRight);
    mainLayout->addWidget(vibrationWidget, 3, 1);

    //---

    positionButton_ = new OnOffButton(this);
    positionButton_->setEnabled(false);
    positionButton_->setChecked(true);

    mainLayout->addWidget(new QLabel("ПОЛОЖЕНИЕ(ГИРОСКОП)"), 4, 0, Qt::AlignRight);
    mainLayout->addWidget(positionButton_, 4, 1);

    //---

    dustButton1_ = new OnOffButton(this);
    dustButton1_->setEnabled(false);
    dustButton1_->setChecked(true);

    dustButton2_ = new OnOffButton(this);
    dustButton2_->setEnabled(false);
    dustButton2_->setChecked(true);

    dustLabel_ = new QLabel(this);
    dustLabel_->setText("встроенный, % | выносной, %");
    dustLabel_->setStyleSheet("color:#ffc000");

    QHBoxLayout* dustLayout = new QHBoxLayout;
    dustLayout->setMargin(0);
    QWidget* dustWidget = new QWidget;
    dustWidget->setLayout(dustLayout);
    dustLayout->addWidget(dustButton1_);
    dustLayout->addWidget(dustButton2_);
    dustLayout->addWidget(dustLabel_);

    mainLayout->addWidget(new QLabel("ЗАПЫЛЕННОСТЬ"), 5, 0, Qt::AlignRight);
    mainLayout->addWidget(dustWidget, 5, 1);

    //---

    moistureLabel_ = new QLabel(this);
    moistureLabel_->setText("значение, %");
    moistureLabel_->setStyleSheet("color:#ffc000");

    moistureButton_ = new OnOffButton(this);
    moistureButton_->setEnabled(false);
    moistureButton_->setChecked(true);

    QHBoxLayout* moistureLayout = new QHBoxLayout;
    moistureLayout->setMargin(0);
    QWidget* moistureWidget = new QWidget;
    moistureWidget->setLayout(moistureLayout);
    moistureLayout->addWidget(moistureButton_);
    moistureLayout->addWidget(moistureLabel_);

    mainLayout->addWidget(new QLabel("ВЛАЖНОСТЬ"), 6, 0, Qt::AlignRight);
    mainLayout->addWidget(moistureWidget, 6, 1);

    //---

    temperatureButton1_ = new OnOffButton(this);
    temperatureButton1_->setEnabled(false);
    temperatureButton1_->setChecked(true);

    temperatureButton2_ = new OnOffButton(this);
    temperatureButton2_->setEnabled(false);
    temperatureButton2_->setChecked(true);

    temperatureButton3_ = new OnOffButton(this);
    temperatureButton3_->setEnabled(false);
    temperatureButton3_->setChecked(false);

    temperatureLabel_ = new QLabel(this);
    temperatureLabel_->setText("датчики 1|2|3");
    temperatureLabel_->setStyleSheet("color:#ffc000");

    QHBoxLayout* temperatureLayout = new QHBoxLayout;
    temperatureLayout->setMargin(0);
    QWidget* temperatureWidget = new QWidget;
    temperatureWidget->setLayout(temperatureLayout);
    temperatureLayout->addWidget(temperatureButton1_);
    temperatureLayout->addWidget(temperatureButton2_);
    temperatureLayout->addWidget(temperatureButton3_);
    temperatureLayout->addWidget(temperatureLabel_);

    mainLayout->addWidget(new QLabel("ТЕМПЕРАТУРА"), 7, 0, Qt::AlignRight);
    mainLayout->addWidget(temperatureWidget, 7, 1);

    //---

    breakInButton1_ = new OnOffButton(this);
    breakInButton1_->setEnabled(false);
    breakInButton1_->setChecked(true);

    breakInButton2_ = new OnOffButton(this);
    breakInButton2_->setEnabled(false);
    breakInButton2_->setChecked(true);

    breakInButton3_ = new OnOffButton(this);
    breakInButton3_->setEnabled(false);
    breakInButton3_->setChecked(true);

    breakInButton4_ = new OnOffButton(this);
    breakInButton4_->setEnabled(false);
    breakInButton4_->setChecked(false);

    breakInLabel_ = new QLabel(this);
    breakInLabel_->setText("датчики 1|2|3|4");
    breakInLabel_->setStyleSheet("color:#ffc000");

    QHBoxLayout* breakInLayout = new QHBoxLayout;
    breakInLayout->setMargin(0);
    QWidget* breakInWidget = new QWidget;
    breakInWidget->setLayout(breakInLayout);
    breakInLayout->addWidget(breakInButton1_);
    breakInLayout->addWidget(breakInButton2_);
    breakInLayout->addWidget(breakInButton3_);
    breakInLayout->addWidget(breakInButton4_);
    breakInLayout->addWidget(breakInLabel_);

    mainLayout->addWidget(new QLabel("ВСКРЫТИЕ"), 8, 0, Qt::AlignRight);
    mainLayout->addWidget(breakInWidget, 8, 1);

    //---

    iButtonButton_ = new OnOffButton(this);
    iButtonButton_->setEnabled(false);
    iButtonButton_->setChecked(true);

    mainLayout->addWidget(new QLabel("МОДУЛЬ IBUTTON"), 9, 0, Qt::AlignRight);
    mainLayout->addWidget(iButtonButton_, 9, 1);
}

void MainFrame::refresh(bool isDeviceConnected)
{
    // Устройство активно

    activityStatusButton_->setChecked(mcuInData_->functionsFlags & FunctionsFlag::turnOn);

	// Статус питания(доступности)

	powerStatusButton_->setChecked(isDeviceConnected);

	// Светодиоды

	ledIndicatorButton1_->setChecked(isDeviceConnected);
	ledIndicatorButton2_->setChecked(isDeviceConnected);

	// Датчики вибрации

	vibrationButton1_->setChecked(isDeviceConnected && mcuInData_->vibrationFlags1 & ActionsFlag::active);
	vibrationButton2_->setChecked(isDeviceConnected && mcuInData_->vibrationFlags2 & ActionsFlag::active);
    vibrationButton3_->setChecked(isDeviceConnected && mcuInData_->vibrationFlags3 & ActionsFlag::active);
    vibrationButton4_->setChecked(isDeviceConnected && mcuInData_->vibrationFlags4 & ActionsFlag::active);

	// Датчик положения
	positionButton_->setChecked(isDeviceConnected && mcuInData_->positionFlags & ActionsFlag::active);

	// Датчики запыленности

	dustButton1_->setChecked(isDeviceConnected && mcuInData_->dustFlags1 & ActionsFlag::active);
	dustButton2_->setChecked(isDeviceConnected && mcuInData_->dustFlags2 & ActionsFlag::active);
    //dustButton3_->setChecked(isDeviceConnected && mcuInData_->dustFlags3 & ActionsFlag::active);
	dustLabel_->setText("недоступно");

	// Датчик влажности

	moistureButton_->setChecked(isDeviceConnected && mcuInData_->moistureFlags & ActionsFlag::active);
	moistureLabel_->setText("недоступно");

	// Датчика температуры

	temperatureButton1_->setChecked(isDeviceConnected && mcuInData_->temperatureFlags1 & ActionsFlag::active);
	temperatureButton2_->setChecked(isDeviceConnected && mcuInData_->temperatureFlags2 & ActionsFlag::active);
	temperatureButton3_->setChecked(isDeviceConnected && mcuInData_->temperatureFlags3 & ActionsFlag::active);
	temperatureLabel_->setText("недоступно");

	// Датчики вскрытия

	breakInButton1_->setChecked(isDeviceConnected && mcuInData_->breakInFlags1 & ActionsFlag::active);
	breakInButton2_->setChecked(isDeviceConnected && mcuInData_->breakInFlags2 & ActionsFlag::active);
	breakInButton3_->setChecked(isDeviceConnected && mcuInData_->breakInFlags3 & ActionsFlag::active);

	// IButton

	iButtonButton_->setChecked(isDeviceConnected);

    if(isDeviceConnected)
	{
		// Датчики вибрации

        if(mcuInData_->vibrationFlags1 & ActionsFlag::active)
		    vibrationButton1_->setAlert(mcuOutData_->vibrationSensor1 > mcuInData_->vibrationMaxValue1);
        if (mcuInData_->vibrationFlags2 & ActionsFlag::active)
		    vibrationButton2_->setAlert(mcuOutData_->vibrationSensor2 > mcuInData_->vibrationMaxValue2);
		if (mcuInData_->vibrationFlags3 & ActionsFlag::active)
			vibrationButton3_->setAlert(mcuOutData_->vibrationSensor2 > mcuInData_->vibrationMaxValue2);

		// Датчики запыленности

        if (mcuInData_->dustFlags1 & ActionsFlag::active)
		    dustButton1_->setAlert(mcuOutData_->dustSensor1 > mcuInData_->dustMaxValue1);
        if (mcuInData_->dustFlags2 & ActionsFlag::active)
		dustButton2_->setAlert(mcuOutData_->dustSensor2 / 10 > mcuInData_->dustMaxValue2);
		    dustLabel_->setText(QString("встроенный - %1 % | выносной - %2 %").arg(mcuOutData_->dustSensor1).arg(mcuOutData_->dustSensor2 / 10));

		// Датчик влажности

        if (mcuInData_->moistureFlags & ActionsFlag::active)
		    moistureButton_->setAlert(mcuOutData_->moistureSensor > mcuInData_->moistureMaxValue);
		moistureLabel_->setText(QString("%1 %").arg(mcuOutData_->moistureSensor));

		// Датчика температуры

        if (mcuInData_->temperatureFlags1 & ActionsFlag::active)
		    temperatureButton1_->setAlert((mcuOutData_->temperatureSensor1 > mcuInData_->temperatureMaxValue1) ||
			    (mcuOutData_->temperatureSensor1 < mcuInData_->temperatureMinValue1));

        if (mcuInData_->temperatureFlags2 & ActionsFlag::active)
		    temperatureButton2_->setAlert((mcuOutData_->temperatureSensor2 > mcuInData_->temperatureMaxValue2) ||
			    (mcuOutData_->temperatureSensor2 < mcuInData_->temperatureMinValue2));

        if (mcuInData_->temperatureFlags3 & ActionsFlag::active)
		    temperatureButton3_->setAlert((mcuOutData_->temperatureSensor3 > mcuInData_->temperatureMaxValue3) ||
			    (mcuOutData_->temperatureSensor3 < mcuInData_->temperatureMinValue3));

		const QChar degreeSign(0260);
		temperatureLabel_->setText(QString("%1 %2C | %3 %4C | %5 %6C").arg(mcuOutData_->temperatureSensor1)
			.arg(degreeSign)
			.arg(mcuOutData_->temperatureSensor2)
			.arg(degreeSign)
			.arg(mcuOutData_->temperatureSensor3)
			.arg(degreeSign));

		// Датчики вскрытия

        if (mcuInData_->breakInFlags1 & ActionsFlag::active)
		    breakInButton1_->setAlert(mcuOutData_->breakInSensor1 != mcuInData_->breakInSensorNormalState1);
        if (mcuInData_->breakInFlags2 & ActionsFlag::active)
		    breakInButton2_->setAlert(mcuOutData_->breakInSensor2 != mcuInData_->breakInSensorNormalState2);
        if (mcuInData_->breakInFlags3 & ActionsFlag::active)
		    breakInButton3_->setAlert(mcuOutData_->breakInSensor3 != mcuInData_->breakInSensorNormalState3);
	}
}
