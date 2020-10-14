#include "dustframe.h"

#include <QHBoxLayout>
#include <QFormLayout>

DustFrame::DustFrame(QSharedPointer<QSettings> settings, McuInData *mcuInData, McuOutData *mcuOutData, QWidget *parent) : Frame(settings, mcuInData, mcuOutData, parent)
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

    QHBoxLayout* actionListTitleLayout1 = new QHBoxLayout;
    actionListTitleLayout1->addStretch();
    actionListTitleLayout1->addWidget(new QLabel("ВЫПОЛНИТЬ ДЕЙСТВИЕ"));
    actionListTitleLayout1->addStretch();

    sensorLayout1->addRow(actionListTitleLayout1);

    notificationButton1_ = new OnOffButton;
    connect(notificationButton1_, &OnOffButton::toggled, [=](){setBit(mcuInData_->dustFlags1, ActionsFlag::notification, notificationButton1_->isChecked());});
    notificationButton1_->setChecked(settings_->value("dustFrame/flags1").toInt() & ActionsFlag::notification);

    soundSignalButton1_ = new OnOffButton;
    connect(soundSignalButton1_, &OnOffButton::toggled, [=](){setBit(mcuInData_->dustFlags1, ActionsFlag::soundSignal, soundSignalButton1_->isChecked());});
    soundSignalButton1_->setChecked(settings_->value("dustFrame/flags1").toInt() & ActionsFlag::soundSignal);

    PCShutDownButton1_ = new OnOffButton;
    connect(PCShutDownButton1_, &OnOffButton::toggled, [=](){setBit(mcuInData_->dustFlags1, ActionsFlag::PCShutDown, PCShutDownButton1_->isChecked());});
    PCShutDownButton1_->setChecked(settings_->value("dustFrame/flags1").toInt() & ActionsFlag::PCShutDown);

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

    QHBoxLayout* actionListTitleLayout2 = new QHBoxLayout;
    actionListTitleLayout2->addStretch();
    actionListTitleLayout2->addWidget(new QLabel("ВЫПОЛНИТЬ ДЕЙСТВИЕ"));
    actionListTitleLayout2->addStretch();

    sensorLayout2->addRow(actionListTitleLayout2);

    notificationButton2_ = new OnOffButton;
    connect(notificationButton2_, &OnOffButton::toggled, [=](){setBit(mcuInData->dustFlags2, ActionsFlag::notification, notificationButton2_->isChecked());});
    notificationButton2_->setChecked(settings_->value("dustFrame/flags2").toInt() & ActionsFlag::notification);

    soundSignalButton2_ = new OnOffButton;
    connect(soundSignalButton2_, &OnOffButton::toggled, [=](){setBit(mcuInData->dustFlags2, ActionsFlag::soundSignal, soundSignalButton2_->isChecked());});
    soundSignalButton2_->setChecked(settings_->value("dustFrame/flags2").toInt() & ActionsFlag::soundSignal);

    PCShutDownButton2_ = new OnOffButton;
    connect(PCShutDownButton2_, &OnOffButton::toggled, [=](){setBit(mcuInData->dustFlags2, ActionsFlag::PCShutDown, PCShutDownButton2_->isChecked());});
    PCShutDownButton2_->setChecked(settings_->value("dustFrame/flags2").toInt() & ActionsFlag::PCShutDown);

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

    QHBoxLayout* actionListTitleLayout3 = new QHBoxLayout;
    actionListTitleLayout3->addStretch();
    actionListTitleLayout3->addWidget(new QLabel("ВЫПОЛНИТЬ ДЕЙСТВИЕ"));
    actionListTitleLayout3->addStretch();

    sensorLayout3->addRow(actionListTitleLayout3);

    notificationButton3_ = new OnOffButton;
    connect(notificationButton3_, &OnOffButton::toggled, [=](){setBit(mcuInData->dustFlags3, ActionsFlag::notification, notificationButton3_->isChecked());});
    notificationButton3_->setChecked(settings_->value("dustFrame/flags3").toInt() & ActionsFlag::notification);

    soundSignalButton3_ = new OnOffButton;
    connect(soundSignalButton3_, &OnOffButton::toggled, [=](){setBit(mcuInData->dustFlags3, ActionsFlag::soundSignal, soundSignalButton3_->isChecked());});
    soundSignalButton3_->setChecked(settings_->value("dustFrame/flags3").toInt() & ActionsFlag::soundSignal);

    PCShutDownButton3_ = new OnOffButton;
    connect(PCShutDownButton3_, &OnOffButton::toggled, [=](){setBit(mcuInData->dustFlags3, ActionsFlag::PCShutDown, PCShutDownButton3_->isChecked());});
    PCShutDownButton3_->setChecked(settings_->value("dustFrame/flags3").toInt() & ActionsFlag::PCShutDown);

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

DustFrame::~DustFrame()
{
    uint8_t flags1 = 0;
    setBit(flags1, ActionsFlag::notification, notificationButton1_->isChecked());
    setBit(flags1, ActionsFlag::soundSignal, soundSignalButton1_->isChecked());
    setBit(flags1, ActionsFlag::PCShutDown, PCShutDownButton1_->isChecked());
    settings_->setValue("dustFrame/flags1", flags1);

    uint8_t flags2 = 0;
    setBit(flags2, ActionsFlag::notification, notificationButton2_->isChecked());
    setBit(flags2, ActionsFlag::soundSignal, soundSignalButton2_->isChecked());
    setBit(flags2, ActionsFlag::PCShutDown, PCShutDownButton2_->isChecked());
    settings_->setValue("dustFrame/flags2", flags2);

    uint8_t flags3 = 0;
    setBit(flags3, ActionsFlag::notification, notificationButton3_->isChecked());
    setBit(flags3, ActionsFlag::soundSignal, soundSignalButton3_->isChecked());
    setBit(flags3, ActionsFlag::PCShutDown, PCShutDownButton3_->isChecked());
    settings_->setValue("dustFrame/flags3", flags3);

    settings_->setValue("dustFrame/maxValue1", maxValue1_->value());
    settings_->setValue("dustFrame/maxValue2", maxValue2_->value());
    settings_->setValue("dustFrame/maxValue3", maxValue3_->value());

    settings_->sync();
}

void DustFrame::refresh()
{
    indicator1_->setValue(mcuOutData_->dustSensor1);
    indicator2_->setValue(mcuOutData_->dustSensor2 / 10);
    indicator3_->setValue(mcuOutData_->dustSensor3);
}

void DustFrame::setControlsEnabled(bool state)
{
    maxValue1_->setEnabled(state);
    maxValue2_->setEnabled(state);
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
