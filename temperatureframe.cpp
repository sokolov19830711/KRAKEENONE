#include "temperatureframe.h"

#include <QHBoxLayout>
#include <QFormLayout>
#include <QDebug>

TemperatureFrame::TemperatureFrame(QSharedPointer<QSettings> settings, McuInData* mcuInData, McuOutData* mcuOutData, QWidget *parent) : Frame(settings, mcuInData, mcuOutData, parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout;
    addMainLayout(mainLayout);

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

    QHBoxLayout* actionListTitleLayout1 = new QHBoxLayout;
    actionListTitleLayout1->addStretch();
    actionListTitleLayout1->addWidget(new QLabel("ВЫПОЛНИТЬ ДЕЙСТВИЕ"));
    actionListTitleLayout1->addStretch();

    sensorLayout1->addRow(actionListTitleLayout1);

    //---

    notificationButton1_ = new OnOffButton;
    connect(notificationButton1_, &OnOffButton::toggled, [=](){setBit(mcuInData_->temperatureFlags1, ActionsFlag::notification, notificationButton1_->isChecked());});
    notificationButton1_->setChecked(settings_->value("temperatureFrame/flags1").toInt() & ActionsFlag::notification);

    soundSignalButton1_ = new OnOffButton;
    connect(soundSignalButton1_, &OnOffButton::toggled, [=](){setBit(mcuInData_->temperatureFlags1, ActionsFlag::soundSignal, soundSignalButton1_->isChecked());});
    soundSignalButton1_->setChecked(settings_->value("temperatureFrame/flags1").toInt() & ActionsFlag::soundSignal);

    PCShutDownButton1_ = new OnOffButton;
    connect(PCShutDownButton1_, &OnOffButton::toggled, [=](){setBit(mcuInData_->temperatureFlags1, ActionsFlag::PCShutDown, PCShutDownButton1_->isChecked());});
    PCShutDownButton1_->setChecked(settings_->value("temperatureFrame/flags1").toInt() & ActionsFlag::PCShutDown);

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

    QHBoxLayout* actionListTitleLayout2 = new QHBoxLayout;
    actionListTitleLayout2->addStretch();
    actionListTitleLayout2->addWidget(new QLabel("ВЫПОЛНИТЬ ДЕЙСТВИЕ"));
    actionListTitleLayout2->addStretch();

    sensorLayout2->addRow(actionListTitleLayout2);

    notificationButton2_ = new OnOffButton;
    connect(notificationButton2_, &OnOffButton::toggled, [=](){setBit(mcuInData_->temperatureFlags2, ActionsFlag::notification, notificationButton2_->isChecked());});
    notificationButton2_->setChecked(settings_->value("temperatureFrame/flags2").toInt() & ActionsFlag::notification);

    soundSignalButton2_ = new OnOffButton;
    connect(soundSignalButton2_, &OnOffButton::toggled, [=](){setBit(mcuInData_->temperatureFlags2, ActionsFlag::soundSignal, soundSignalButton2_->isChecked());});
    soundSignalButton2_->setChecked(settings_->value("temperatureFrame/flags2").toInt() & ActionsFlag::soundSignal);

    PCShutDownButton2_ = new OnOffButton;
    connect(PCShutDownButton2_, &OnOffButton::toggled, [=](){setBit(mcuInData_->temperatureFlags2, ActionsFlag::PCShutDown, PCShutDownButton2_->isChecked());});
    PCShutDownButton2_->setChecked(settings_->value("temperatureFrame/flags2").toInt() & ActionsFlag::PCShutDown);

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

    QHBoxLayout* actionListTitleLayout3 = new QHBoxLayout;
    actionListTitleLayout3->addStretch();
    actionListTitleLayout3->addWidget(new QLabel("ВЫПОЛНИТЬ ДЕЙСТВИЕ"));
    actionListTitleLayout3->addStretch();

    sensorLayout3->addRow(actionListTitleLayout3);

    notificationButton3_ = new OnOffButton;
    connect(notificationButton3_, &OnOffButton::toggled, [=](){setBit(mcuInData_->temperatureFlags3, ActionsFlag::notification, notificationButton3_->isChecked());});
    notificationButton3_->setChecked(settings_->value("temperatureFrame/flags3").toInt() & ActionsFlag::notification);

    soundSignalButton3_ = new OnOffButton;
    connect(soundSignalButton3_, &OnOffButton::toggled, [=](){setBit(mcuInData_->temperatureFlags3, ActionsFlag::soundSignal, soundSignalButton3_->isChecked());});
    soundSignalButton3_->setChecked(settings_->value("temperatureFrame/flags3").toInt() & ActionsFlag::soundSignal);

    PCShutDownButton3_ = new OnOffButton;
    connect(PCShutDownButton3_, &OnOffButton::toggled, [=](){setBit(mcuInData_->temperatureFlags3, ActionsFlag::PCShutDown, PCShutDownButton3_->isChecked());});
    PCShutDownButton3_->setChecked(settings_->value("temperatureFrame/flags3").toInt() & ActionsFlag::PCShutDown);

    QFormLayout* actionsLayout3 = new QFormLayout;

    actionsLayout3->addRow("Сообщение администратору", notificationButton3_);
    actionsLayout3->addRow("Звуковой сигнал", soundSignalButton3_);
    actionsLayout3->addRow("Выключение ПК", PCShutDownButton3_);

    QHBoxLayout* actionsAlignedLayout3 = new QHBoxLayout;
    actionsAlignedLayout3->addStretch();
    actionsAlignedLayout3->addLayout(actionsLayout3);
    actionsAlignedLayout3->addStretch();

    sensorLayout3->addRow(actionsAlignedLayout3);

    //---

}

TemperatureFrame::~TemperatureFrame()
{
    uint8_t flags1 = 0;
    setBit(flags1, ActionsFlag::notification, notificationButton1_->isChecked());
    setBit(flags1, ActionsFlag::soundSignal, soundSignalButton1_->isChecked());
    setBit(flags1, ActionsFlag::PCShutDown, PCShutDownButton1_->isChecked());
    settings_->setValue("temperatureFrame/flags1", flags1);

    uint8_t flags2 = 0;
    setBit(flags2, ActionsFlag::notification, notificationButton2_->isChecked());
    setBit(flags2, ActionsFlag::soundSignal, soundSignalButton2_->isChecked());
    setBit(flags2, ActionsFlag::PCShutDown, PCShutDownButton2_->isChecked());
    settings_->setValue("temperatureFrame/flags2", flags2);

    uint8_t flags3 = 0;
    setBit(flags3, ActionsFlag::notification, notificationButton3_->isChecked());
    setBit(flags3, ActionsFlag::soundSignal, soundSignalButton3_->isChecked());
    setBit(flags3, ActionsFlag::PCShutDown, PCShutDownButton3_->isChecked());
    settings_->setValue("temperatureFrame/flags3", flags3);

    settings_->setValue("temperatureFrame/maxValue1", maxValue1_->value());
    settings_->setValue("temperatureFrame/maxValue2", maxValue2_->value());
    settings_->setValue("temperatureFrame/maxValue3", maxValue3_->value());

    settings_->setValue("temperatureFrame/minValue1", minValue1_->value());
    settings_->setValue("temperatureFrame/minValue2", minValue2_->value());
    settings_->setValue("temperatureFrame/minValue3", minValue3_->value());

    settings_->sync();
}

void TemperatureFrame::refresh()
{
    indicator1_->setValue(mcuOutData_->temperatureSensor1);
    indicator2_->setValue(mcuOutData_->temperatureSensor2);
    indicator3_->setValue(mcuOutData_->temperatureSensor3);
}

void TemperatureFrame::setControlsEnabled(bool state)
{
    minValue1_->setEnabled(state);
    maxValue1_->setEnabled(state);

    minValue2_->setEnabled(state);
    maxValue2_->setEnabled(state);

    minValue3_->setEnabled(state);
    maxValue3_->setEnabled(state);

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
