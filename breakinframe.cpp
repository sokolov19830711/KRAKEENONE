#include "breakinframe.h"

#include <QHBoxLayout>
#include <QFormLayout>
#include <QDebug>

BreakInFrame::BreakInFrame(QSharedPointer<QSettings> settings, McuInData *mcuInData, McuOutData *mcuOutData, QWidget *parent) : Frame(settings, mcuInData, mcuOutData, parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout;
    addMainLayout(mainLayout);

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
    sensorName1_ = new QLabel("ДАТЧИК ВСТРОЕННЫЙ");
    sensorName1_->setAlignment(Qt::AlignCenter);
    name1Layout->addWidget(sensorName1_);
    name1Layout->addStretch();

    sensorLayout1->addRow(name1Layout);

	QString switchButtonsStyle = "QPushButton{height : 30; width : 80; color: #ffffff; border-style:none; border-color:#7f7f7f; background-color:#595959;}"
		"QPushButton:checked{font : bold; color: #ffffff; border-style:none; border-color:#7f7f7f; background-color:#00b050;}";

    settingsButtons1_ = new SwitchButtonsWidget(1, 2, switchButtonsStyle, {"РАЗОМКНУТ", "ЗАМКНУТ" }, this);
    settingsButtons1_->setChecked(settings_->value("breakInFrame/sensorState1").toInt());
    connect(settingsButtons1_, &SwitchButtonsWidget::idClicked, [=]() {mcuInData_->breakInSensorNormalState1 = settingsButtons1_->checkedId(); });

    QHBoxLayout* settingsButtons1Layout = new QHBoxLayout;
    settingsButtons1Layout->addStretch();
    settingsButtons1Layout->addWidget(settingsButtons1_);
    settingsButtons1Layout->addStretch();

    sensorLayout1->addRow(settingsButtons1Layout);

    sensorLayout1->addRow(new QLabel()); // Пустая строка для разделения

	_actionsSetupWidget1 = new ActionsSetupWidget(&(mcuInData_->breakInFlags1), { ActionsFlag::notification, ActionsFlag::soundSignal, ActionsFlag::PCShutDown }, this);
	sensorLayout1->addRow(_actionsSetupWidget1);

    //---

    QHBoxLayout* name2Layout = new QHBoxLayout;
    name2Layout->addStretch();
    sensorName2_ = new QLabel("ДАТЧИК ВЫНОСНОЙ");
    sensorName2_->setAlignment(Qt::AlignCenter);
    name2Layout->addWidget(sensorName2_);
    name2Layout->addStretch();

    sensorLayout2->addRow(name2Layout);

	settingsButtons2_ = new SwitchButtonsWidget(1, 2, switchButtonsStyle, { "РАЗОМКНУТ", "ЗАМКНУТ" }, this);
	settingsButtons2_->setChecked(settings_->value("breakInFrame/sensorState2").toInt());
	connect(settingsButtons2_, &SwitchButtonsWidget::idClicked, [=]() {mcuInData_->breakInSensorNormalState2 = settingsButtons2_->checkedId(); });

    QHBoxLayout* settingsButtons2Layout = new QHBoxLayout;
    settingsButtons2Layout->addStretch();
    settingsButtons2Layout->addWidget(settingsButtons2_);
    settingsButtons2Layout->addStretch();

    sensorLayout2->addRow(settingsButtons2Layout);

    sensorLayout2->addRow(new QLabel()); // Пустая строка для разделения

	_actionsSetupWidget2 = new ActionsSetupWidget(&(mcuInData_->breakInFlags2), { ActionsFlag::notification, ActionsFlag::soundSignal, ActionsFlag::PCShutDown }, this);
	sensorLayout2->addRow(_actionsSetupWidget2);

    //---

    QHBoxLayout* name3Layout = new QHBoxLayout;
    name3Layout->addStretch();
    sensorName3_ = new QLabel("ДАТЧИК ВЫНОСНОЙ");
    sensorName3_->setAlignment(Qt::AlignCenter);
    name3Layout->addWidget(sensorName3_);
    name3Layout->addStretch();

    sensorLayout3->addRow(name3Layout);

	settingsButtons3_ = new SwitchButtonsWidget(1, 2, switchButtonsStyle, { "РАЗОМКНУТ", "ЗАМКНУТ" }, this);
	settingsButtons3_->setChecked(settings_->value("breakInFrame/sensorState3").toInt());
	connect(settingsButtons3_, &SwitchButtonsWidget::idClicked, [=]() {mcuInData_->breakInSensorNormalState3 = settingsButtons3_->checkedId(); });

    QHBoxLayout* settingsButtons3Layout = new QHBoxLayout;
    settingsButtons3Layout->addStretch();
    settingsButtons3Layout->addWidget(settingsButtons3_);
    settingsButtons3Layout->addStretch();

    sensorLayout3->addRow(settingsButtons3Layout);

    sensorLayout3->addRow(new QLabel()); // Пустая строка для разделения

	_actionsSetupWidget3 = new ActionsSetupWidget(&(mcuInData_->breakInFlags3), { ActionsFlag::notification, ActionsFlag::soundSignal, ActionsFlag::PCShutDown }, this);
	sensorLayout3->addRow(_actionsSetupWidget3);
}

BreakInFrame::~BreakInFrame()
{
	settings_->setValue("breakInFrame/flags1", _actionsSetupWidget1->flags());
	settings_->setValue("breakInFrame/flags2", _actionsSetupWidget2->flags());
	settings_->setValue("breakInFrame/flags3", _actionsSetupWidget3->flags());

    settings_->setValue("breakInFrame/sensorState1", settingsButtons1_->checkedId());
    settings_->setValue("breakInFrame/sensorState2", settingsButtons2_->checkedId());
    settings_->setValue("breakInFrame/sensorState3", settingsButtons3_->checkedId());

    settings_->sync();
}

void BreakInFrame::refresh(bool isDeviceConnected)
{
    
}