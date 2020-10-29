#include "dustframe.h"

#include <QHBoxLayout>
#include <QFormLayout>

DustFrame::DustFrame(QSharedPointer<QSettings> settings, McuInData *mcuInData, McuOutData *mcuOutData, QWidget *parent) : Frame(settings, mcuInData, mcuOutData, parent)
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
	_switchSensorsButtons->setChecked(0, mcuInData_->dustFlags1 & ActionsFlag::active);
	_switchSensorsButtons->setChecked(1, mcuInData_->dustFlags2 & ActionsFlag::active);
	_switchSensorsButtons->setChecked(2, mcuInData_->dustFlags3 & ActionsFlag::active);

	connect(_switchSensorsButtons, &SwitchButtonsWidget::idToggled, [=](int id, bool checked)
		{
			switch (id)
			{
			case 0:
				setBit(mcuInData_->dustFlags1, ActionsFlag::active, checked);
				break;
			case 1:
				setBit(mcuInData_->dustFlags2, ActionsFlag::active, checked);
				break;
			case 2:
				setBit(mcuInData_->dustFlags3, ActionsFlag::active, checked);
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
    mainLayout->addSpacing(40);
    mainLayout->addLayout(sensorLayout2);
    mainLayout->addSpacing(40);
    mainLayout->addLayout(sensorLayout3);

    //---

    QHBoxLayout* name1Layout = new QHBoxLayout;
    name1Layout->addStretch();
    QLabel* name1 = new QLabel("ДАТЧИК ЗАПЫЛЕННОСТИ\n(ВСТРОЕННЫЙ)");
    name1->setAlignment(Qt::AlignCenter);
    name1Layout->addWidget(name1);
    name1Layout->addStretch();

    sensorLayout1->addRow(name1Layout);

    indicator1_ = new SensorInicator;

    QHBoxLayout* value1Layout = new QHBoxLayout;
    value1Layout->addStretch();
    value1Layout->addWidget(indicator1_);
    value1Layout->addStretch();

    sensorLayout1->addRow(value1Layout);

    maxValue1_ = new SpinBox;
    connect(maxValue1_, SIGNAL(valueChanged(int)), indicator1_, SLOT(setMaxNormal(int)));
    connect(maxValue1_, &SpinBox::valueChanged, [=](){mcuInData_->dustMaxValue1 = maxValue1_->value();});
    maxValue1_->setValue(settings_->value("dustFrame/maxValue1").toInt());

    QHBoxLayout* limits1Layout = new QHBoxLayout;
    limits1Layout->addStretch();
    limits1Layout->addWidget(maxValue1_);
    limits1Layout->addStretch();
    sensorLayout1->addRow(limits1Layout);

    sensorLayout1->addRow(new QLabel()); // Пустая строка для разделения

	_actionsSetupWidget1 = new ActionsSetupWidget(&(mcuInData_->dustFlags1), { ActionsFlag::notification, ActionsFlag::soundSignal, ActionsFlag::PCShutDown }, this);
	sensorLayout1->addRow(_actionsSetupWidget1);

    //---

    QHBoxLayout* name2Layout = new QHBoxLayout;
    name2Layout->addStretch();
    QLabel* name2 = new QLabel("ДАТЧИК ЗАПЫЛЕННОСТИ\n(ВЫНОСНОЙ, ТИП 1)");
    name2->setAlignment(Qt::AlignCenter);
    name2Layout->addWidget(name2);
    name2Layout->addStretch();

    sensorLayout2->addRow(name2Layout);

    indicator2_ = new SensorInicator;

    QHBoxLayout* value2Layout = new QHBoxLayout;
    value2Layout->addStretch();
    value2Layout->addWidget(indicator2_);
    value2Layout->addStretch();

    sensorLayout2->addRow(value2Layout);

    maxValue2_ = new SpinBox;
    connect(maxValue2_, SIGNAL(valueChanged(int)), indicator2_, SLOT(setMaxNormal(int)));
    connect(maxValue2_, &SpinBox::valueChanged, [=](){mcuInData_->dustMaxValue2 = maxValue2_->value();});
    maxValue2_->setValue(settings_->value("dustFrame/maxValue2").toInt());

    QHBoxLayout* limits2Layout = new QHBoxLayout;
    limits2Layout->addStretch();
    limits2Layout->addWidget(maxValue2_);
    limits2Layout->addStretch();
    sensorLayout2->addRow(limits2Layout);

    sensorLayout2->addRow(new QLabel()); // Пустая строка для разделения

	_actionsSetupWidget2 = new ActionsSetupWidget(&(mcuInData_->dustFlags2), { ActionsFlag::notification, ActionsFlag::soundSignal, ActionsFlag::PCShutDown }, this);
	sensorLayout2->addRow(_actionsSetupWidget2);

    //---

    QHBoxLayout* name3Layout = new QHBoxLayout;
    name3Layout->addStretch();
    QLabel* name3 = new QLabel("ДАТЧИК ЗАПЫЛЕННОСТИ\n(ВЫНОСНОЙ, ТИП 2)");
    name3->setAlignment(Qt::AlignCenter);
    name3Layout->addWidget(name3);
    name3Layout->addStretch();

    sensorLayout3->addRow(name3Layout);

    indicator3_ = new SensorInicator;

    QHBoxLayout* value3Layout = new QHBoxLayout;
    value3Layout->addStretch();
    value3Layout->addWidget(indicator3_);
    value3Layout->addStretch();

    sensorLayout3->addRow(value3Layout);

    maxValue3_ = new SpinBox;
    connect(maxValue3_, SIGNAL(valueChanged(int)), indicator3_, SLOT(setMaxNormal(int)));
    connect(maxValue3_, &SpinBox::valueChanged, [=](){mcuInData_->dustMaxValue3 = maxValue3_->value();});
    maxValue3_->setValue(settings_->value("dustFrame/maxValue3").toInt());

    QHBoxLayout* limits3Layout = new QHBoxLayout;
    limits3Layout->addStretch();
    limits3Layout->addWidget(maxValue3_);
    limits3Layout->addStretch();
    sensorLayout3->addRow(limits3Layout);

    sensorLayout3->addRow(new QLabel()); // Пустая строка для разделения

	_actionsSetupWidget3 = new ActionsSetupWidget(&(mcuInData_->dustFlags3), { ActionsFlag::notification, ActionsFlag::soundSignal, ActionsFlag::PCShutDown }, this);
	sensorLayout3->addRow(_actionsSetupWidget3);

    //---

}

DustFrame::~DustFrame()
{
    settings_->setValue("dustFrame/flags1", _actionsSetupWidget1->flags());
    settings_->setValue("dustFrame/flags2", _actionsSetupWidget2->flags());
    settings_->setValue("dustFrame/flags3", _actionsSetupWidget3->flags());

    settings_->setValue("dustFrame/maxValue1", maxValue1_->value());
    settings_->setValue("dustFrame/maxValue2", maxValue2_->value());
    settings_->setValue("dustFrame/maxValue3", maxValue3_->value());

    settings_->sync();
}

void DustFrame::refresh(bool isDeviceConnected)
{
    if(isDeviceConnected)
	{
        mcuInData_->dustFlags1 & ActionsFlag::active ? indicator1_->setValue(mcuOutData_->dustSensor1) : indicator1_->setActive(false);
        mcuInData_->dustFlags2 & ActionsFlag::active ? indicator2_->setValue(mcuOutData_->dustSensor2 / 10) : indicator2_->setActive(false);
        mcuInData_->dustFlags3 & ActionsFlag::active ? indicator3_->setValue(mcuOutData_->dustSensor3) : indicator3_->setActive(false);
	}

    else
    {
        indicator1_->setActive(false);
        indicator2_->setActive(false);
        indicator3_->setActive(false);
    }
}
