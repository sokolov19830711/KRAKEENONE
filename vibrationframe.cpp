#include "vibrationframe.h"

#include <QHBoxLayout>
#include <QFormLayout>

VibrationFrame::VibrationFrame(QSharedPointer<QSettings> settings, McuInData* mcuInData, McuOutData* mcuOutData, QWidget *parent) : Frame(settings, mcuInData, mcuOutData, parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout;
    addMainLayout(mainLayout);

    //---
	QString switchButtonsStyle = "QPushButton{color: #ffffff; border-style:none; border-color:#7f7f7f; background-color:#595959;}"
		"QPushButton:checked{font : bold; color: #ffffff; border-style:none; border-color:#7f7f7f; background-color:#00b050;}";

    _switchSensorsButtons = new SwitchButtonsWidget(1, 4, switchButtonsStyle, { "1", "2", "3", "4" }, this);
    _switchSensorsButtons->setGeometry(670, 0, 100, 50);
    _switchSensorsButtons->setButtonsSize(20, 30);
    _switchSensorsButtons->setSpacing(4);
    _switchSensorsButtons->setExclusive(false);
    _switchSensorsButtons->setChecked(0, mcuInData_->vibrationFlags1 & ActionsFlag::active);
    _switchSensorsButtons->setChecked(1, mcuInData_->vibrationFlags2 & ActionsFlag::active);
    _switchSensorsButtons->setChecked(2, mcuInData_->vibrationFlags3 & ActionsFlag::active);
    _switchSensorsButtons->setChecked(3, mcuInData_->vibrationFlags4 & ActionsFlag::active);

    connect(_switchSensorsButtons, &SwitchButtonsWidget::idToggled, [=](int id, bool checked) 
        {
            switch (id)
            {
            case 0:
                setBit(mcuInData_->vibrationFlags1, ActionsFlag::active, checked);
                break;
			case 1:
                setBit(mcuInData_->vibrationFlags2, ActionsFlag::active, checked);
				break;
			case 2:
                setBit(mcuInData_->vibrationFlags3, ActionsFlag::active, checked);
				break;
			case 3:
                setBit(mcuInData_->vibrationFlags4, ActionsFlag::active, checked);
				break;
            default:
                break;
            }
        });

    //---

    QFormLayout* sensorLayout1 = new QFormLayout;
    QFormLayout* sensorLayout2 = new QFormLayout;
    QFormLayout* sensorLayout3 = new QFormLayout;
    QFormLayout* sensorLayout4 = new QFormLayout;

    mainLayout->addLayout(sensorLayout1);
    mainLayout->addSpacing(40);
    mainLayout->addLayout(sensorLayout2);
    mainLayout->addSpacing(40);
    mainLayout->addLayout(sensorLayout3);
    mainLayout->addSpacing(40);
    mainLayout->addLayout(sensorLayout4);

    //---

    QHBoxLayout* name1Layout = new QHBoxLayout;
    name1Layout->addStretch();
    name1Layout->addWidget(new QLabel("ДАТЧИК ВИБРАЦИИ №1"));
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
    connect(maxValue1_, &SpinBox::valueChanged, [=](){mcuInData_->vibrationMaxValue1 = maxValue1_->value();});
    maxValue1_->setValue(settings_->value("vibrationFrame/maxValue1").toInt());

    QHBoxLayout* limits1Layout = new QHBoxLayout;

    limits1Layout->addStretch();
    limits1Layout->addWidget(maxValue1_);
    limits1Layout->addStretch();

    sensorLayout1->addRow(limits1Layout);
    sensorLayout1->addRow(new QLabel()); // Пустая строка для разделения

    _actionsSetupWidget1 = new ActionsSetupWidget(&(mcuInData_->vibrationFlags1), { ActionsFlag::notification, ActionsFlag::soundSignal, ActionsFlag::PCShutDown }, this);
    sensorLayout1->addRow(_actionsSetupWidget1);

    //---

    QHBoxLayout* name2Layout = new QHBoxLayout;
    name2Layout->addStretch();
    name2Layout->addWidget(new QLabel("ДАТЧИК ВИБРАЦИИ №2"));
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
    connect(maxValue2_, &SpinBox::valueChanged, [=](){mcuInData_->vibrationMaxValue2 = maxValue2_->value();});
    maxValue2_->setValue(settings_->value("vibrationFrame/maxValue2").toInt());

    QHBoxLayout* limits2Layout = new QHBoxLayout;

    limits2Layout->addStretch();
    limits2Layout->addWidget(maxValue2_);
    limits2Layout->addStretch();

    sensorLayout2->addRow(limits2Layout);
    sensorLayout2->addRow(new QLabel()); // Пустая строка для разделения

	_actionsSetupWidget2 = new ActionsSetupWidget(&(mcuInData_->vibrationFlags2), { ActionsFlag::notification, ActionsFlag::soundSignal, ActionsFlag::PCShutDown }, this);
	sensorLayout2->addRow(_actionsSetupWidget2);

    //---

    QHBoxLayout* name3Layout = new QHBoxLayout;
    name3Layout->addStretch();
    name3Layout->addWidget(new QLabel("ДАТЧИК ВИБРАЦИИ №3"));
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
    connect(maxValue3_, &SpinBox::valueChanged, [=](){mcuInData_->vibrationMaxValue3 = maxValue3_->value();});
    maxValue3_->setValue(settings_->value("vibrationFrame/maxValue3").toInt());

    QHBoxLayout* limits3Layout = new QHBoxLayout;

    limits3Layout->addStretch();
    limits3Layout->addWidget(maxValue3_);
    limits3Layout->addStretch();

    sensorLayout3->addRow(limits3Layout);
    sensorLayout3->addRow(new QLabel()); // Пустая строка для разделения

	_actionsSetupWidget3 = new ActionsSetupWidget(&(mcuInData_->vibrationFlags3), { ActionsFlag::notification, ActionsFlag::soundSignal, ActionsFlag::PCShutDown }, this);
	sensorLayout3->addRow(_actionsSetupWidget3);

    //---

    QHBoxLayout* name4Layout = new QHBoxLayout;
    name4Layout->addStretch();
    name4Layout->addWidget(new QLabel("ДАТЧИК ВИБРАЦИИ №4"));
    name4Layout->addStretch();

    sensorLayout4->addRow(name4Layout);

    indicator4_ = new SensorInicator;

    QHBoxLayout* value4Layout = new QHBoxLayout;
    value4Layout->addStretch();
    value4Layout->addWidget(indicator4_);
    value4Layout->addStretch();

    sensorLayout4->addRow(value4Layout);

    maxValue4_ = new SpinBox;
    connect(maxValue4_, SIGNAL(valueChanged(int)), indicator4_, SLOT(setMaxNormal(int)));
    connect(maxValue4_, &SpinBox::valueChanged, [=](){mcuInData_->vibrationMaxValue4 = maxValue4_->value();});
    maxValue4_->setValue(settings_->value("vibrationFrame/maxValue4").toInt());

    QHBoxLayout* limits4Layout = new QHBoxLayout;

    limits4Layout->addStretch();
    limits4Layout->addWidget(maxValue4_);
    limits4Layout->addStretch();

    sensorLayout4->addRow(limits4Layout);
    sensorLayout4->addRow(new QLabel()); // Пустая строка для разделения

	_actionsSetupWidget4 = new ActionsSetupWidget(&(mcuInData_->vibrationFlags4), { ActionsFlag::notification, ActionsFlag::soundSignal, ActionsFlag::PCShutDown }, this);
	sensorLayout4->addRow(_actionsSetupWidget4);

    //---

    connect(maxValue1_, SIGNAL(valueChanged(int)), indicator1_, SLOT(setMaxNormal(int)));
    connect(maxValue2_, SIGNAL(valueChanged(int)), indicator2_, SLOT(setMaxNormal(int)));
    connect(maxValue3_, SIGNAL(valueChanged(int)), indicator3_, SLOT(setMaxNormal(int)));
    connect(maxValue4_, SIGNAL(valueChanged(int)), indicator4_, SLOT(setMaxNormal(int)));
}

VibrationFrame::~VibrationFrame()
{
    settings_->setValue("vibrationFrame/flags1", _actionsSetupWidget1->flags());
    settings_->setValue("vibrationFrame/flags2", _actionsSetupWidget2->flags());
    settings_->setValue("vibrationFrame/flags3", _actionsSetupWidget3->flags());
    settings_->setValue("vibrationFrame/flags4", _actionsSetupWidget4->flags());

    settings_->setValue("vibrationFrame/maxValue1", maxValue1_->value());
    settings_->setValue("vibrationFrame/maxValue2", maxValue2_->value());
    settings_->setValue("vibrationFrame/maxValue3", maxValue3_->value());
    settings_->setValue("vibrationFrame/maxValue4", maxValue4_->value());

    settings_->sync();
}

void VibrationFrame::refresh(bool isDeviceConnected)
{
    if(isDeviceConnected)
	{
        mcuInData_->vibrationFlags1 & ActionsFlag::active ? indicator1_->setValue(mcuOutData_->vibrationSensor1) : indicator1_->setActive(false);
        mcuInData_->vibrationFlags2 & ActionsFlag::active ? indicator2_->setValue(mcuOutData_->vibrationSensor2) : indicator2_->setActive(false);
        mcuInData_->vibrationFlags3 & ActionsFlag::active ? indicator3_->setValue(mcuOutData_->vibrationSensor3) : indicator3_->setActive(false);
        mcuInData_->vibrationFlags4 & ActionsFlag::active ? indicator4_->setValue(mcuOutData_->vibrationSensor4) : indicator4_->setActive(false);
	}

    else
    {
        indicator1_->setActive(false);
        indicator2_->setActive(false);
        indicator3_->setActive(false);
        indicator4_->setActive(false);
    }
}

