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

    _actionsSetupWidget = new ActionsSetupWidget(&(mcuInData_->moistureFlags), {ActionsFlag::notification, ActionsFlag::soundSignal, ActionsFlag::PCShutDown}, this);
    sensorLayout1->addRow(_actionsSetupWidget);
}

MoistureFrame::~MoistureFrame()
{
    settings_->setValue("moistureFrame/flags", _actionsSetupWidget->flags());

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

    _actionsSetupWidget->setEnabled(state);
}
