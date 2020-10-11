#include "vibrationframe.h"

#include <QHBoxLayout>
#include <QFormLayout>

VibrationFrame::VibrationFrame(QSharedPointer<QSettings> settings, McuInData* mcuInData, McuOutData* mcuOutData, QWidget *parent) : Frame(settings, mcuInData, mcuOutData, parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout;
    addMainLayout(mainLayout);

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

    QHBoxLayout* actionListTitleLayout1 = new QHBoxLayout;
    actionListTitleLayout1->addStretch();
    actionListTitleLayout1->addWidget(new QLabel("ВЫПОЛНИТЬ ДЕЙСТВИЕ"));
    actionListTitleLayout1->addStretch();

    sensorLayout1->addRow(actionListTitleLayout1);

    notificationButton1_ = new OnOffButton;
    connect(notificationButton1_, &OnOffButton::toggled, [=](){setBit(mcuInData_->vibrationFlags1, ActionsFlag::notification, notificationButton1_->isChecked());});
    notificationButton1_->setChecked(settings_->value("vibrationFrame/flags1").toInt() & ActionsFlag::notification);

    soundSignalButton1_ = new OnOffButton;
    connect(soundSignalButton1_, &OnOffButton::toggled, [=](){setBit(mcuInData_->vibrationFlags1, ActionsFlag::soundSignal, soundSignalButton1_->isChecked());});
    soundSignalButton1_->setChecked(settings_->value("vibrationFrame/flags1").toInt() & ActionsFlag::soundSignal);

    PCShutDownButton1_ = new OnOffButton;
    connect(PCShutDownButton1_, &OnOffButton::toggled, [=](){setBit(mcuInData_->vibrationFlags1, ActionsFlag::PCShutDown, PCShutDownButton1_->isChecked());});
    PCShutDownButton1_->setChecked(settings_->value("vibrationFrame/flags1").toInt() & ActionsFlag::PCShutDown);

    QFormLayout* actionsLayout1 = new QFormLayout;

    actionsLayout1->addRow("Сообщение\nадминистратору", notificationButton1_);
    actionsLayout1->addRow("Звуковой сигнал", soundSignalButton1_);
    actionsLayout1->addRow("Выключение ПК", PCShutDownButton1_);

    sensorLayout1->addRow(actionsLayout1);

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

    QHBoxLayout* actionListTitleLayout2 = new QHBoxLayout;
    actionListTitleLayout2->addStretch();
    actionListTitleLayout2->addWidget(new QLabel("ВЫПОЛНИТЬ ДЕЙСТВИЕ"));
    actionListTitleLayout2->addStretch();

    sensorLayout2->addRow(actionListTitleLayout2);


    notificationButton2_ = new OnOffButton;
    connect(notificationButton2_, &OnOffButton::toggled, [=](){setBit(mcuInData_->vibrationFlags2, ActionsFlag::notification, notificationButton2_->isChecked());});
    notificationButton2_->setChecked(settings_->value("vibrationFrame/flags2").toInt() & ActionsFlag::notification);

    soundSignalButton2_ = new OnOffButton;
    connect(soundSignalButton2_, &OnOffButton::toggled, [=](){setBit(mcuInData_->vibrationFlags2, ActionsFlag::soundSignal, soundSignalButton2_->isChecked());});
    soundSignalButton2_->setChecked(settings_->value("vibrationFrame/flags2").toInt() & ActionsFlag::soundSignal);

    PCShutDownButton2_ = new OnOffButton;
    connect(PCShutDownButton2_, &OnOffButton::toggled, [=](){setBit(mcuInData_->vibrationFlags2, ActionsFlag::PCShutDown, PCShutDownButton2_->isChecked());});
    PCShutDownButton2_->setChecked(settings_->value("vibrationFrame/flags2").toInt() & ActionsFlag::PCShutDown);

    QFormLayout* actionsLayout2 = new QFormLayout;

    actionsLayout2->addRow("Сообщение\nадминистратору", notificationButton2_);
    actionsLayout2->addRow("Звуковой сигнал", soundSignalButton2_);
    actionsLayout2->addRow("Выключение ПК", PCShutDownButton2_);

    sensorLayout2->addRow(actionsLayout2);

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

    QHBoxLayout* actionListTitleLayout3 = new QHBoxLayout;
    actionListTitleLayout3->addStretch();
    actionListTitleLayout3->addWidget(new QLabel("ВЫПОЛНИТЬ ДЕЙСТВИЕ"));
    actionListTitleLayout3->addStretch();

    sensorLayout3->addRow(actionListTitleLayout3);


    notificationButton3_ = new OnOffButton;
    connect(notificationButton3_, &OnOffButton::toggled, [=](){setBit(mcuInData_->vibrationFlags3, ActionsFlag::notification, notificationButton3_->isChecked());});
    notificationButton3_->setChecked(settings_->value("vibrationFrame/flags3").toInt() & ActionsFlag::notification);

    soundSignalButton3_ = new OnOffButton;
    connect(soundSignalButton3_, &OnOffButton::toggled, [=](){setBit(mcuInData_->vibrationFlags3, ActionsFlag::soundSignal, soundSignalButton3_->isChecked());});
    soundSignalButton3_->setChecked(settings_->value("vibrationFrame/flags3").toInt() & ActionsFlag::soundSignal);

    PCShutDownButton3_ = new OnOffButton;
    connect(PCShutDownButton3_, &OnOffButton::toggled, [=](){setBit(mcuInData_->vibrationFlags3, ActionsFlag::PCShutDown, PCShutDownButton3_->isChecked());});
    PCShutDownButton3_->setChecked(settings_->value("vibrationFrame/flags3").toInt() & ActionsFlag::PCShutDown);

    QFormLayout* actionsLayout3 = new QFormLayout;

    actionsLayout3->addRow("Сообщение\nадминистратору", notificationButton3_);
    actionsLayout3->addRow("Звуковой сигнал", soundSignalButton3_);
    actionsLayout3->addRow("Выключение ПК", PCShutDownButton3_);

    sensorLayout3->addRow(actionsLayout3);

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

    QHBoxLayout* actionListTitleLayout4 = new QHBoxLayout;
    actionListTitleLayout4->addStretch();
    actionListTitleLayout4->addWidget(new QLabel("ВЫПОЛНИТЬ ДЕЙСТВИЕ"));
    actionListTitleLayout4->addStretch();

    sensorLayout4->addRow(actionListTitleLayout4);


    notificationButton4_ = new OnOffButton;
    connect(notificationButton4_, &OnOffButton::toggled, [=](){setBit(mcuInData_->vibrationFlags4, ActionsFlag::notification, notificationButton4_->isChecked());});
    notificationButton4_->setChecked(settings_->value("vibrationFrame/flags4").toInt() & ActionsFlag::notification);

    soundSignalButton4_ = new OnOffButton;
    connect(soundSignalButton4_, &OnOffButton::toggled, [=](){setBit(mcuInData_->vibrationFlags4, ActionsFlag::soundSignal, soundSignalButton4_->isChecked());});
    soundSignalButton1_->setChecked(settings_->value("vibrationFrame/flags1").toInt() & ActionsFlag::soundSignal);

    PCShutDownButton4_ = new OnOffButton;
    connect(PCShutDownButton4_, &OnOffButton::toggled, [=](){setBit(mcuInData_->vibrationFlags4, ActionsFlag::PCShutDown, PCShutDownButton4_->isChecked());});
    PCShutDownButton4_->setChecked(settings_->value("vibrationFrame/flags4").toInt() & ActionsFlag::PCShutDown);

    QFormLayout* actionsLayout4 = new QFormLayout;

    actionsLayout4->addRow("Сообщение\nадминистратору", notificationButton4_);
    actionsLayout4->addRow("Звуковой сигнал", soundSignalButton4_);
    actionsLayout4->addRow("Выключение ПК", PCShutDownButton4_);

    sensorLayout4->addRow(actionsLayout4);

    //---

    connect(maxValue1_, SIGNAL(valueChanged(int)), indicator1_, SLOT(setMaxNormal(int)));
    connect(maxValue2_, SIGNAL(valueChanged(int)), indicator2_, SLOT(setMaxNormal(int)));
    connect(maxValue3_, SIGNAL(valueChanged(int)), indicator3_, SLOT(setMaxNormal(int)));
    connect(maxValue4_, SIGNAL(valueChanged(int)), indicator4_, SLOT(setMaxNormal(int)));
}

VibrationFrame::~VibrationFrame()
{
    uint8_t flags1 = 0;
    setBit(flags1, ActionsFlag::notification, notificationButton1_->isChecked());
    setBit(flags1, ActionsFlag::soundSignal, soundSignalButton1_->isChecked());
    setBit(flags1, ActionsFlag::PCShutDown, PCShutDownButton1_->isChecked());
    settings_->setValue("vibrationFrame/flags1", flags1);

    uint8_t flags2 = 0;
    setBit(flags2, ActionsFlag::notification, notificationButton2_->isChecked());
    setBit(flags2, ActionsFlag::soundSignal, soundSignalButton2_->isChecked());
    setBit(flags2, ActionsFlag::PCShutDown, PCShutDownButton2_->isChecked());
    settings_->setValue("vibrationFrame/flags2", flags2);

    uint8_t flags3 = 0;
    setBit(flags3, ActionsFlag::notification, notificationButton3_->isChecked());
    setBit(flags3, ActionsFlag::soundSignal, soundSignalButton3_->isChecked());
    setBit(flags3, ActionsFlag::PCShutDown, PCShutDownButton3_->isChecked());
    settings_->setValue("vibrationFrame/flags3", flags3);

    uint8_t flags4 = 0;
    setBit(flags4, ActionsFlag::notification, notificationButton4_->isChecked());
    setBit(flags4, ActionsFlag::soundSignal, soundSignalButton4_->isChecked());
    setBit(flags4, ActionsFlag::PCShutDown, PCShutDownButton4_->isChecked());
    settings_->setValue("vibrationFrame/flags4", flags4);

    settings_->setValue("vibrationFrame/maxValue1", maxValue1_->value());
    settings_->setValue("vibrationFrame/maxValue2", maxValue2_->value());
    settings_->setValue("vibrationFrame/maxValue3", maxValue3_->value());
    settings_->setValue("vibrationFrame/maxValue4", maxValue4_->value());

    settings_->sync();
}

void VibrationFrame::refresh()
{
    indicator1_->setValue(mcuOutData_->vibrationSensor1);
    indicator2_->setValue(mcuOutData_->vibrationSensor2);
    indicator3_->setValue(mcuOutData_->vibrationSensor3);
    indicator4_->setValue(mcuOutData_->vibrationSensor4);
}

void VibrationFrame::setControlsEnabled(bool state)
{
    maxValue1_->setEnabled(state);
    maxValue2_->setEnabled(state);
    maxValue3_->setEnabled(state);
    maxValue4_->setEnabled(state);

    notificationButton1_->setEnabled(state);
    soundSignalButton1_->setEnabled(state);
    PCShutDownButton1_->setEnabled(state);

    notificationButton2_->setEnabled(state);
    soundSignalButton2_->setEnabled(state);
    PCShutDownButton2_->setEnabled(state);

    notificationButton3_->setEnabled(state);
    soundSignalButton3_->setEnabled(state);
    PCShutDownButton3_->setEnabled(state);

    notificationButton4_->setEnabled(state);
    soundSignalButton4_->setEnabled(state);
    PCShutDownButton4_->setEnabled(state);
}
