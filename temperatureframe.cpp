#include "temperatureframe.h"

#include <QHBoxLayout>
#include <QFormLayout>
#include <QDebug>

TemperatureFrame::TemperatureFrame(QSharedPointer<QSettings> settings, McuInData* mcuInData, McuOutData* mcuOutData, QWidget *parent) : Frame(settings, mcuInData, mcuOutData, parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout;
    addMainLayout(mainLayout);

	//---
	QString switchButtonsStyle = "QPushButton{color: #ffffff; border-style:none; border-color:#7f7f7f; background-color:#595959;}"
		"QPushButton:checked{font : bold; color: #ffffff; border-style:none; border-color:#7f7f7f; background-color:#00b050;}";

	_switchSensorsButtons = new SwitchButtonsWidget(1, 3, switchButtonsStyle, { "1", "2", "3" }, this);
	_switchSensorsButtons->setGeometry(670, 0, 75, 50);
	_switchSensorsButtons->setButtonsSize(20, 30);
	_switchSensorsButtons->setSpacing(4);
	_switchSensorsButtons->setExclusive(false);
	_switchSensorsButtons->setChecked(0, mcuInData_->temperatureFlags1 & ActionsFlag::active);
	_switchSensorsButtons->setChecked(1, mcuInData_->temperatureFlags2 & ActionsFlag::active);
	_switchSensorsButtons->setChecked(2, mcuInData_->temperatureFlags3 & ActionsFlag::active);

	connect(_switchSensorsButtons, &SwitchButtonsWidget::idToggled, [=](int id, bool checked)
		{
			switch (id)
			{
			case 0:
				setBit(mcuInData_->temperatureFlags1, ActionsFlag::active, checked);
				break;
			case 1:
				setBit(mcuInData_->temperatureFlags2, ActionsFlag::active, checked);
				break;
			case 2:
				setBit(mcuInData_->temperatureFlags3, ActionsFlag::active, checked);
				break;
			default:
				break;
			}
		});

	//---

    QFormLayout* sensorLayout1 = new QFormLayout;
    QFormLayout* sensorLayout2 = new QFormLayout;
    QFormLayout* sensorLayout3 = new QFormLayout;

    mainLayout->addLayout(sensorLayout1);
    mainLayout->addSpacing(18);
    mainLayout->addLayout(sensorLayout2);
    mainLayout->addSpacing(18);
    mainLayout->addLayout(sensorLayout3);

    //---

    sensorName1_ = new QLabel;
    sensorName1_->setText("ДАТЧИК ТЕМПЕРАТУРЫ 1");

    QHBoxLayout* name1Layout = new QHBoxLayout;
    name1Layout->addStretch();
    name1Layout->addWidget(sensorName1_);
    name1Layout->addStretch();

    sensorLayout1->addRow(name1Layout);

    indicator1_ = new SensorInicator;

    QHBoxLayout* value1Layout = new QHBoxLayout;
    value1Layout->addStretch();
    value1Layout->addWidget(indicator1_);
    value1Layout->addStretch();

    sensorLayout1->addRow(value1Layout);

    minValue1_ = new SpinBox;
    minValue1_->setTitle("мин");
    connect(minValue1_, SIGNAL(valueChanged(int)), indicator1_, SLOT(setMinNormal(int)));
    connect(minValue1_, &SpinBox::valueChanged, [=](){mcuInData_->temperatureMinValue1 = minValue1_->value();});
    minValue1_->setValue(settings_->value("temperatureFrame/minValue1").toInt());

    maxValue1_ = new SpinBox;
    maxValue1_->setTitle("макс");
    connect(maxValue1_, SIGNAL(valueChanged(int)), indicator1_, SLOT(setMaxNormal(int)));
    connect(maxValue1_, &SpinBox::valueChanged, [=](){mcuInData_->temperatureMaxValue1 = maxValue1_->value();});
    maxValue1_->setValue(settings_->value("temperatureFrame/maxValue1").toInt());

    QHBoxLayout* limits1Layout = new QHBoxLayout;
    limits1Layout->addStretch();
    limits1Layout->addWidget(minValue1_);
    limits1Layout->addWidget(maxValue1_);
    limits1Layout->addStretch();
    sensorLayout1->addRow(limits1Layout);

    sensorLayout1->addRow(new QLabel()); // Пустая строка для разделения

	_actionsSetupWidget1 = new ActionsSetupWidget(&(mcuInData_->temperatureFlags1), { ActionsFlag::notification, ActionsFlag::soundSignal, ActionsFlag::PCShutDown }, this);
	sensorLayout1->addRow(_actionsSetupWidget1);

    //---

    sensorName2_ = new QLabel;
    sensorName2_->setText("ДАТЧИК ТЕМПЕРАТУРЫ 2");

    QHBoxLayout* name2Layout = new QHBoxLayout;
    name2Layout->addStretch();
    name2Layout->addWidget(sensorName2_);
    name2Layout->addStretch();

    sensorLayout2->addRow(name2Layout);

    indicator2_ = new SensorInicator;

    QHBoxLayout* value2Layout = new QHBoxLayout;
    value2Layout->addStretch();
    value2Layout->addWidget(indicator2_);
    value2Layout->addStretch();

    sensorLayout2->addRow(value2Layout);

    minValue2_ = new SpinBox;
    minValue2_->setTitle("мин");
    connect(minValue2_, SIGNAL(valueChanged(int)), indicator2_, SLOT(setMinNormal(int)));
    connect(minValue2_, &SpinBox::valueChanged, [=](){mcuInData_->temperatureMinValue2 = minValue2_->value();});
    minValue2_->setValue(settings_->value("temperatureFrame/minValue2").toInt());

    maxValue2_ = new SpinBox;
    maxValue2_->setTitle("макс");
    connect(maxValue2_, SIGNAL(valueChanged(int)), indicator2_, SLOT(setMaxNormal(int)));
    connect(maxValue2_, &SpinBox::valueChanged, [=](){mcuInData_->temperatureMaxValue2 = maxValue2_->value();});
    maxValue2_->setValue(settings_->value("temperatureFrame/maxValue2").toInt());

    QHBoxLayout* limits2Layout = new QHBoxLayout;
    limits2Layout->addStretch();
    limits2Layout->addWidget(minValue2_);
    limits2Layout->addWidget(maxValue2_);
    sensorLayout2->addRow(limits2Layout);
    limits2Layout->addStretch();

    sensorLayout2->addRow(new QLabel()); // Пустая строка для разделения

	_actionsSetupWidget2 = new ActionsSetupWidget(&(mcuInData_->temperatureFlags2), { ActionsFlag::notification, ActionsFlag::soundSignal, ActionsFlag::PCShutDown }, this);
	sensorLayout2->addRow(_actionsSetupWidget2);

    //---

    sensorName3_ = new QLabel;
    sensorName3_->setText("ДАТЧИК ТЕМПЕРАТУРЫ 3");

    QHBoxLayout* name3Layout = new QHBoxLayout;
    name3Layout->addStretch();
    name3Layout->addWidget(sensorName3_);
    name3Layout->addStretch();

    sensorLayout3->addRow(name3Layout);

    indicator3_ = new SensorInicator;

    QHBoxLayout* value3Layout = new QHBoxLayout;
    value3Layout->addStretch();
    value3Layout->addWidget(indicator3_);
    value3Layout->addStretch();

    sensorLayout3->addRow(value3Layout);

    minValue3_ = new SpinBox;
    minValue3_->setTitle("мин");
    connect(minValue3_, SIGNAL(valueChanged(int)), indicator3_, SLOT(setMinNormal(int)));
    connect(minValue3_, &SpinBox::valueChanged, [=](){mcuInData_->temperatureMinValue3 = minValue3_->value();});
    minValue3_->setValue(settings_->value("temperatureFrame/minValue3").toInt());

    maxValue3_ = new SpinBox;
    maxValue3_->setTitle("макс");
    connect(maxValue3_, SIGNAL(valueChanged(int)), indicator3_, SLOT(setMaxNormal(int)));
    connect(maxValue3_, &SpinBox::valueChanged, [=](){mcuInData_->temperatureMaxValue3 = maxValue3_->value();});
    maxValue3_->setValue(settings_->value("temperatureFrame/maxValue3").toInt());

    QHBoxLayout* limits3Layout = new QHBoxLayout;
    limits3Layout->addStretch();
    limits3Layout->addWidget(minValue3_);
    limits3Layout->addWidget(maxValue3_);
    sensorLayout3->addRow(limits3Layout);
    limits3Layout->addStretch();

    sensorLayout3->addRow(new QLabel()); // Пустая строка для разделения

	_actionsSetupWidget3 = new ActionsSetupWidget(&(mcuInData_->temperatureFlags3), { ActionsFlag::notification, ActionsFlag::soundSignal, ActionsFlag::PCShutDown }, this);
	sensorLayout3->addRow(_actionsSetupWidget3);

    QLabel* valueTitle1 = new QLabel("Отображает текущее значение", this);
    valueTitle1->setGeometry(62, 108, 180, 12);
    valueTitle1->setStyleSheet("font-size:7pt; color:#ffc000");
    valueTitle1->setAlignment(Qt::AlignCenter);

    QLabel* limitsTitle1 = new QLabel("Установите критическую величину", this);
    limitsTitle1->setGeometry(62, 178, 180, 16);
    limitsTitle1->setStyleSheet("font-size:7pt; color:#ffc000");
    limitsTitle1->setAlignment(Qt::AlignCenter);

    QLabel* valueTitle2 = new QLabel("Отображает текущее значение", this);
    valueTitle2->setGeometry(308, 108, 180, 12);
    valueTitle2->setStyleSheet("font-size:7pt; color:#ffc000");
    valueTitle2->setAlignment(Qt::AlignCenter);

    QLabel* limitsTitle2 = new QLabel("Установите критическую величину", this);
    limitsTitle2->setGeometry(308, 178, 180, 16);
    limitsTitle2->setStyleSheet("font-size:7pt; color:#ffc000");
    limitsTitle2->setAlignment(Qt::AlignCenter);

    QLabel* valueTitle3 = new QLabel("Отображает текущее значение", this);
    valueTitle3->setGeometry(550, 108, 180, 12);
    valueTitle3->setStyleSheet("font-size:7pt; color:#ffc000");
    valueTitle3->setAlignment(Qt::AlignCenter);

    QLabel* limitsTitle3 = new QLabel("Установите критическую величину", this);
    limitsTitle3->setGeometry(550, 178, 180, 16);
    limitsTitle3->setStyleSheet("font-size:7pt; color:#ffc000");
    limitsTitle3->setAlignment(Qt::AlignCenter);

    //---

}

TemperatureFrame::~TemperatureFrame()
{
	settings_->setValue("temperatureFrame/flags1", _actionsSetupWidget1->flags());
	settings_->setValue("temperatureFrame/flags2", _actionsSetupWidget2->flags());
	settings_->setValue("temperatureFrame/flags3", _actionsSetupWidget3->flags());

    settings_->setValue("temperatureFrame/maxValue1", maxValue1_->value());
    settings_->setValue("temperatureFrame/maxValue2", maxValue2_->value());
    settings_->setValue("temperatureFrame/maxValue3", maxValue3_->value());

    settings_->setValue("temperatureFrame/minValue1", minValue1_->value());
    settings_->setValue("temperatureFrame/minValue2", minValue2_->value());
    settings_->setValue("temperatureFrame/minValue3", minValue3_->value());

    settings_->sync();
}

void TemperatureFrame::refresh(bool isDeviceConnected)
{
    if(isDeviceConnected)
	{
		mcuInData_->temperatureFlags1 & ActionsFlag::active ? indicator1_->setValue(mcuOutData_->temperatureSensor1) : indicator1_->setActive(false);
		mcuInData_->temperatureFlags2 & ActionsFlag::active ? indicator2_->setValue(mcuOutData_->temperatureSensor2) : indicator2_->setActive(false);
		mcuInData_->temperatureFlags3 & ActionsFlag::active ? indicator3_->setValue(mcuOutData_->temperatureSensor3) : indicator3_->setActive(false);
	}

    else
    {
        indicator1_->setActive(false);
        indicator2_->setActive(false);
        indicator3_->setActive(false);
    }
}
