#include "moistureframe.h"

#include <QHBoxLayout>
#include <QFormLayout>

MoistureFrame::MoistureFrame(QSharedPointer<QSettings> settings, McuInData *mcuInData, McuOutData *mcuOutData, QWidget *parent) : Frame(settings, mcuInData, mcuOutData, parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout;
    addMainLayout(mainLayout);

    QFormLayout* sensorLayout1 = new QFormLayout;
    mainLayout->addLayout(sensorLayout1);

    //---

    QHBoxLayout* name1Layout = new QHBoxLayout;
    name1Layout->addStretch();
    name1Layout->addWidget(new QLabel("ДАТЧИК ВЛАЖНОСТИ"));
    name1Layout->addStretch();

    sensorLayout1->addRow(name1Layout);

    indicator_ = new SensorInicator;

    QHBoxLayout* value1Layout = new QHBoxLayout;
    value1Layout->addStretch();
    value1Layout->addWidget(indicator_);
    value1Layout->addStretch();

    sensorLayout1->addRow(value1Layout);

    minValue_ = new SpinBox;
    minValue_->setTitle("мин");
    connect(minValue_, SIGNAL(valueChanged(int)), indicator_, SLOT(setMinNormal(int)));
    connect(minValue_, &SpinBox::valueChanged, [=](){mcuInData_->moistureMinValue = minValue_->value();});
    minValue_->setValue(settings_->value("moistureFrame/minValue").toInt());

    maxValue_ = new SpinBox;
    maxValue_->setTitle("макс");
    connect(maxValue_, SIGNAL(valueChanged(int)), indicator_, SLOT(setMaxNormal(int)));
    connect(maxValue_, &SpinBox::valueChanged, [=](){mcuInData_->moistureMaxValue = maxValue_->value();});
    maxValue_->setValue(settings_->value("moistureFrame/maxValue").toInt());

    QHBoxLayout* limits1Layout = new QHBoxLayout;
    limits1Layout->addStretch();
    limits1Layout->addWidget(minValue_);
    limits1Layout->addWidget(maxValue_);
    limits1Layout->addStretch();
    sensorLayout1->addRow(limits1Layout);

    sensorLayout1->addRow(new QLabel()); // Пустая строка для разделения

    QHBoxLayout* actionListTitleLayout1 = new QHBoxLayout;
    actionListTitleLayout1->addStretch();
    actionListTitleLayout1->addWidget(new QLabel("ВЫПОЛНИТЬ ДЕЙСТВИЕ"));
    actionListTitleLayout1->addStretch();

    sensorLayout1->addRow(actionListTitleLayout1);

    notificationButton_ = new OnOffButton;
    connect(notificationButton_, &OnOffButton::toggled, [=](){setBit(mcuInData_->moistureFlags, ActionsFlag::notification, notificationButton_->isChecked());});
    notificationButton_->setChecked(settings_->value("moistureFrame/flags").toInt() & ActionsFlag::notification);

    soundSignalButton_ = new OnOffButton;
    connect(soundSignalButton_, &OnOffButton::toggled, [=](){setBit(mcuInData_->moistureFlags, ActionsFlag::soundSignal, soundSignalButton_->isChecked());});
    soundSignalButton_->setChecked(settings_->value("moistureFrame/flags").toInt() & ActionsFlag::soundSignal);

    PCShutDownButton_ = new OnOffButton;
    connect(PCShutDownButton_, &OnOffButton::toggled, [=](){setBit(mcuInData_->moistureFlags, ActionsFlag::PCShutDown, PCShutDownButton_->isChecked());});
    PCShutDownButton_->setChecked(settings_->value("moistureFrame/flags").toInt() & ActionsFlag::PCShutDown);

    QFormLayout* actionsLayout1 = new QFormLayout;

    actionsLayout1->addRow("Сообщение администратору", notificationButton_);
    actionsLayout1->addRow("Звуковой сигнал", soundSignalButton_);
    actionsLayout1->addRow("Выключение ПК", PCShutDownButton_);

    QHBoxLayout* actionsAlignedLayout1 = new QHBoxLayout;
    actionsAlignedLayout1->addStretch();
    actionsAlignedLayout1->addLayout(actionsLayout1);
    actionsAlignedLayout1->addStretch();

    sensorLayout1->addRow(actionsAlignedLayout1);

    //---

}

MoistureFrame::~MoistureFrame()
{
    uint8_t flags = 0;
    setBit(flags, ActionsFlag::notification, notificationButton_->isChecked());
    setBit(flags, ActionsFlag::soundSignal, soundSignalButton_->isChecked());
    setBit(flags, ActionsFlag::PCShutDown, PCShutDownButton_->isChecked());
    settings_->setValue("moistureFrame/flags", flags);

    settings_->setValue("moistureFrame/maxValue", maxValue_->value());
    settings_->setValue("moistureFrame/minValue", minValue_->value());

    settings_->sync();
}

void MoistureFrame::refresh()
{
    indicator_->setValue(mcuOutData_->moistureSensor);
}

void MoistureFrame::setControlsEnabled(bool state)
{
    minValue_->setEnabled(state);
    maxValue_->setEnabled(state);

    notificationButton_->setEnabled(state);
    soundSignalButton_->setEnabled(state);
    PCShutDownButton_->setEnabled(state);
}
