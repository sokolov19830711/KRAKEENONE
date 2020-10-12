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

    settingsButtons1_ = new ButtonGroup({"РАЗОМКНУТ", "ЗАМКНУТ" }, 75, 25, this);
    settingsButtons1_->setChecked(settings_->value("breakInFrame/sensorState1").toInt());
    connect(settingsButtons1_, &ButtonGroup::idClicked, [=]() {setBit(mcuInData_->breakInSensorsStates, 0x1, settingsButtons1_->checkedId() - 1); });

    QHBoxLayout* settingsButtons1Layout = new QHBoxLayout;
    settingsButtons1Layout->addStretch();
    settingsButtons1Layout->addWidget(settingsButtons1_);
    settingsButtons1Layout->addStretch();

    sensorLayout1->addRow(settingsButtons1Layout);

    sensorLayout1->addRow(new QLabel()); // Пустая строка для разделения

    QHBoxLayout* actionListTitleLayout1 = new QHBoxLayout;
    actionListTitleLayout1->addStretch();
    actionListTitleLayout1->addWidget(new QLabel("ВЫПОЛНИТЬ ДЕЙСТВИЕ"));
    actionListTitleLayout1->addStretch();

    sensorLayout1->addRow(actionListTitleLayout1);

    notificationButton1_ = new OnOffButton;
    connect(notificationButton1_, &OnOffButton::toggled, [=](){setBit(mcuInData_->breakInFlags1, ActionsFlag::notification, notificationButton1_->isChecked());});
    notificationButton1_->setChecked(settings_->value("breakInFrame/flags1").toInt() & ActionsFlag::notification);

    soundSignalButton1_ = new OnOffButton;
    connect(soundSignalButton1_, &OnOffButton::toggled, [=](){setBit(mcuInData_->breakInFlags1, ActionsFlag::soundSignal, soundSignalButton1_->isChecked());});
    soundSignalButton1_->setChecked(settings_->value("breakInFrame/flags1").toInt() & ActionsFlag::soundSignal);

    PCShutDownButton1_ = new OnOffButton;
    connect(PCShutDownButton1_, &OnOffButton::toggled, [=](){setBit(mcuInData_->breakInFlags1, ActionsFlag::PCShutDown, PCShutDownButton1_->isChecked());});
    PCShutDownButton1_->setChecked(settings_->value("breakInFrame/flags1").toInt() & ActionsFlag::PCShutDown);

    QFormLayout* actionsLayout1 = new QFormLayout;

    actionsLayout1->addRow("Сообщение администратору", notificationButton1_);
    actionsLayout1->addRow("Звуковой сигнал", soundSignalButton1_);
    actionsLayout1->addRow("Выключение ПК", PCShutDownButton1_);

    QHBoxLayout* actionsAlignedLayout1 = new QHBoxLayout;
    actionsAlignedLayout1->addStretch();
    actionsAlignedLayout1->addLayout(actionsLayout1);
    actionsAlignedLayout1->addStretch();

    sensorLayout1->addRow(actionsAlignedLayout1);

    //---

    QHBoxLayout* name2Layout = new QHBoxLayout;
    name2Layout->addStretch();
    sensorName2_ = new QLabel("ДАТЧИК ВСТРОЕННЫЙ");
    sensorName2_->setAlignment(Qt::AlignCenter);
    name2Layout->addWidget(sensorName2_);
    name2Layout->addStretch();

    sensorLayout2->addRow(name2Layout);

    settingsButtons2_ = new ButtonGroup({ "РАЗОМКНУТ", "ЗАМКНУТ" }, 75, 25, this);
    settingsButtons2_->setChecked(settings_->value("breakInFrame/sensorState2").toInt());
    connect(settingsButtons2_, &ButtonGroup::idClicked, [=]() {setBit(mcuInData_->breakInSensorsStates, 0x2, settingsButtons2_->checkedId() - 1); });

    QHBoxLayout* settingsButtons2Layout = new QHBoxLayout;
    settingsButtons2Layout->addStretch();
    settingsButtons2Layout->addWidget(settingsButtons2_);
    settingsButtons2Layout->addStretch();

    sensorLayout2->addRow(settingsButtons2Layout);

    sensorLayout2->addRow(new QLabel()); // Пустая строка для разделения

    QHBoxLayout* actionListTitleLayout2 = new QHBoxLayout;
    actionListTitleLayout2->addStretch();
    actionListTitleLayout2->addWidget(new QLabel("ВЫПОЛНИТЬ ДЕЙСТВИЕ"));
    actionListTitleLayout2->addStretch();

    sensorLayout2->addRow(actionListTitleLayout2);

    notificationButton2_ = new OnOffButton;
    connect(notificationButton2_, &OnOffButton::toggled, [=](){setBit(mcuInData_->breakInFlags2, ActionsFlag::notification, notificationButton2_->isChecked());});
    notificationButton2_->setChecked(settings_->value("breakInFrame/flags2").toInt() & ActionsFlag::notification);

    soundSignalButton2_ = new OnOffButton;
    connect(soundSignalButton2_, &OnOffButton::toggled, [=](){setBit(mcuInData_->breakInFlags2, ActionsFlag::soundSignal, soundSignalButton2_->isChecked());});
    soundSignalButton2_->setChecked(settings_->value("breakInFrame/flags2").toInt() & ActionsFlag::soundSignal);

    PCShutDownButton2_ = new OnOffButton;
    connect(PCShutDownButton2_, &OnOffButton::toggled, [=](){setBit(mcuInData_->breakInFlags2, ActionsFlag::PCShutDown, PCShutDownButton2_->isChecked());});
    PCShutDownButton2_->setChecked(settings_->value("breakInFrame/flags2").toInt() & ActionsFlag::PCShutDown);

    QFormLayout* actionsLayout2 = new QFormLayout;

    actionsLayout2->addRow("Сообщение администратору", notificationButton2_);
    actionsLayout2->addRow("Звуковой сигнал", soundSignalButton2_);
    actionsLayout2->addRow("Выключение ПК", PCShutDownButton2_);

    QHBoxLayout* actionsAlignedLayout2 = new QHBoxLayout;
    actionsAlignedLayout2->addStretch();
    actionsAlignedLayout2->addLayout(actionsLayout2);
    actionsAlignedLayout2->addStretch();

    sensorLayout2->addRow(actionsAlignedLayout2);

    //---

    QHBoxLayout* name3Layout = new QHBoxLayout;
    name3Layout->addStretch();
    sensorName3_ = new QLabel("ДАТЧИК ВСТРОЕННЫЙ");
    sensorName3_->setAlignment(Qt::AlignCenter);
    name3Layout->addWidget(sensorName3_);
    name3Layout->addStretch();

    sensorLayout3->addRow(name3Layout);

    settingsButtons3_ = new ButtonGroup({ "РАЗОМКНУТ", "ЗАМКНУТ" }, 75, 25, this);
    settingsButtons3_->setChecked(settings_->value("breakInFrame/sensorState3").toInt());
    connect(settingsButtons3_, &ButtonGroup::idClicked, [=]() {setBit(mcuInData_->breakInSensorsStates, 0x4, settingsButtons3_->checkedId() - 1); });

    QHBoxLayout* settingsButtons3Layout = new QHBoxLayout;
    settingsButtons3Layout->addStretch();
    settingsButtons3Layout->addWidget(settingsButtons3_);
    settingsButtons3Layout->addStretch();

    sensorLayout3->addRow(settingsButtons3Layout);

    sensorLayout3->addRow(new QLabel()); // Пустая строка для разделения

    QHBoxLayout* actionListTitleLayout3 = new QHBoxLayout;
    actionListTitleLayout3->addStretch();
    actionListTitleLayout3->addWidget(new QLabel("ВЫПОЛНИТЬ ДЕЙСТВИЕ"));
    actionListTitleLayout3->addStretch();

    sensorLayout3->addRow(actionListTitleLayout3);

    notificationButton3_ = new OnOffButton;
    connect(notificationButton3_, &OnOffButton::toggled, [=](){setBit(mcuInData_->breakInFlags3, ActionsFlag::notification, notificationButton3_->isChecked());});
    notificationButton3_->setChecked(settings_->value("breakInFrame/flags3").toInt() & ActionsFlag::notification);

    soundSignalButton3_ = new OnOffButton;
    connect(soundSignalButton3_, &OnOffButton::toggled, [=](){setBit(mcuInData_->breakInFlags3, ActionsFlag::soundSignal, soundSignalButton3_->isChecked());});
    soundSignalButton3_->setChecked(settings_->value("breakInFrame/flags3").toInt() & ActionsFlag::soundSignal);

    PCShutDownButton3_ = new OnOffButton;
    connect(PCShutDownButton3_, &OnOffButton::toggled, [=](){setBit(mcuInData_->breakInFlags3, ActionsFlag::PCShutDown, PCShutDownButton3_->isChecked());});
    PCShutDownButton3_->setChecked(settings_->value("breakInFrame/flags3").toInt() & ActionsFlag::PCShutDown);

    QFormLayout* actionsLayout3 = new QFormLayout;

    actionsLayout3->addRow("Сообщение администратору", notificationButton3_);
    actionsLayout3->addRow("Звуковой сигнал", soundSignalButton3_);
    actionsLayout3->addRow("Выключение ПК", PCShutDownButton3_);

    QHBoxLayout* actionsAlignedLayout3 = new QHBoxLayout;
    actionsAlignedLayout3->addStretch();
    actionsAlignedLayout3->addLayout(actionsLayout3);
    actionsAlignedLayout3->addStretch();

    sensorLayout3->addRow(actionsAlignedLayout3);
}

BreakInFrame::~BreakInFrame()
{
    uint8_t flags1 = 0;
    setBit(flags1, ActionsFlag::notification, notificationButton1_->isChecked());
    setBit(flags1, ActionsFlag::soundSignal, soundSignalButton1_->isChecked());
    setBit(flags1, ActionsFlag::PCShutDown, PCShutDownButton1_->isChecked());
    settings_->setValue("breakInFrame/flags1", flags1);

    uint8_t flags2 = 0;
    setBit(flags2, ActionsFlag::notification, notificationButton2_->isChecked());
    setBit(flags2, ActionsFlag::soundSignal, soundSignalButton2_->isChecked());
    setBit(flags2, ActionsFlag::PCShutDown, PCShutDownButton2_->isChecked());
    settings_->setValue("breakInFrame/flags2", flags2);

    uint8_t flags3 = 0;
    setBit(flags3, ActionsFlag::notification, notificationButton3_->isChecked());
    setBit(flags3, ActionsFlag::soundSignal, soundSignalButton3_->isChecked());
    setBit(flags3, ActionsFlag::PCShutDown, PCShutDownButton3_->isChecked());
    settings_->setValue("breakInFrame/flags3", flags3);

    settings_->setValue("breakInFrame/sensorState1", settingsButtons1_->checkedId());
    settings_->setValue("breakInFrame/sensorState2", settingsButtons2_->checkedId());
    settings_->setValue("breakInFrame/sensorState3", settingsButtons3_->checkedId());

    settings_->sync();
}

void BreakInFrame::refresh()
{

}

void BreakInFrame::setControlsEnabled(bool state)
{
    settingsButtons1_->setEnabled(state);
    settingsButtons2_->setEnabled(state);
    settingsButtons3_->setEnabled(state);

    notificationButton1_->setEnabled(state);
    soundSignalButton1_->setEnabled(state);
    PCShutDownButton1_->setEnabled(state);

    notificationButton2_->setEnabled(state);
    soundSignalButton2_->setEnabled(state);
    PCShutDownButton2_->setEnabled(state);

    notificationButton3_->setEnabled(state);
    soundSignalButton3_->setEnabled(state);
    PCShutDownButton3_->setEnabled(state);
}
