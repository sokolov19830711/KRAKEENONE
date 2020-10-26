#include "positionframe.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>

PositionFrame::PositionFrame(QSharedPointer<QSettings> settings, McuInData *mcuInData, McuOutData *mcuOutData, QWidget *parent) : Frame(settings, mcuInData, mcuOutData, parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    addMainLayout(mainLayout);

    //---

    QHBoxLayout* titleLayout = new QHBoxLayout;
    titleLayout->addStretch();
    titleLayout->addWidget(new QLabel("ДАТЧИК ПОЛОЖЕНИЯ"));
    titleLayout->addStretch();

    mainLayout->addLayout(titleLayout);
    mainLayout->addSpacing(20);

    //---

    QHBoxLayout* currentPositionLayout = new QHBoxLayout;

    currentPositionLayout->addStretch();

    QLabel* xLabel = new QLabel("X:");
    xLabel->setStyleSheet("font-size:12pt; color:#ffffff");
    currentPositionLayout->addWidget(xLabel);
    xValue_ = new SensorInicator;
    currentPositionLayout->addWidget(xValue_);
    currentPositionLayout->addSpacing(50);

    QLabel* yLabel = new QLabel("Y:");
    yLabel->setStyleSheet("font-size:12pt; color:#ffffff");
    currentPositionLayout->addWidget(yLabel);
    yValue_ = new SensorInicator;
    currentPositionLayout->addWidget(yValue_);
    currentPositionLayout->addSpacing(50);

    QLabel* zLabel = new QLabel("Z:");
    zLabel->setStyleSheet("font-size:12pt; color:#ffffff");
    currentPositionLayout->addWidget(zLabel);
    zValue_ = new SensorInicator;
    currentPositionLayout->addWidget(zValue_);
    currentPositionLayout->addSpacing(50);

    saveStartingPositionButton_ = new QPushButton("СОХРАНИТЬ");
    saveStartingPositionButton_->setFixedSize(100, 20);
    saveStartingPositionButton_->setToolTip("Сохранить текущее положение");
    currentPositionLayout->addWidget(saveStartingPositionButton_);

    resetStartingPositionButton_ = new QPushButton("СБРОСИТЬ");
    resetStartingPositionButton_->setFixedSize(100, 20);
    resetStartingPositionButton_->setToolTip("Сбросить сохраненное положение");
    currentPositionLayout->addWidget(resetStartingPositionButton_);

    currentPositionLayout->addStretch();

    mainLayout->addLayout(currentPositionLayout);
    mainLayout->addSpacing(20);

    //---

    QHBoxLayout* limitsLayout = new QHBoxLayout;

    xLimit_ = new SpinBox;
    xLimit_->setTitle("X");
    connect(xLimit_, &SpinBox::valueChanged, [=](){mcuInData_->positionXdeviation = xLimit_->value();});
    xLimit_->setValue(settings_->value("positionFrame/positionXdeviation").toInt());

    yLimit_ = new SpinBox;
    yLimit_->setTitle("Y");
    connect(yLimit_, &SpinBox::valueChanged, [=](){mcuInData_->positionYdeviation = yLimit_->value();});
    yLimit_->setValue(settings_->value("positionFrame/positionYdeviation").toInt());

    zLimit_ = new SpinBox;
    zLimit_->setTitle("Z");
    connect(zLimit_, &SpinBox::valueChanged, [=](){mcuInData_->positionZdeviation = zLimit_->value();});
    zLimit_->setValue(settings_->value("positionFrame/positionZdeviation").toInt());

    resetlimitsButton_ = new QPushButton("СБРОСИТЬ");
    resetlimitsButton_->setFixedSize(100, 42);
    resetlimitsButton_->setToolTip("Сбросить сохраненные ограничения");

    limitsLayout->addStretch();
    limitsLayout->addWidget(xLimit_);
    limitsLayout->addWidget(yLimit_);
    limitsLayout->addWidget(zLimit_);
    limitsLayout->addWidget(resetlimitsButton_);
    limitsLayout->addStretch();

    mainLayout->addLayout(limitsLayout);

    //---

    QHBoxLayout* limitsTitleLayout = new QHBoxLayout;

    QLabel* limitsTitle = new QLabel("Введите критическую величину отклонения в % от\nсохраненного положения");
    limitsTitle->setStyleSheet("font-size:8pt; font:italic; color:#ffc000");
    limitsTitle->setAlignment(Qt::AlignCenter);

    limitsTitleLayout->addStretch();
    limitsTitleLayout->addWidget(limitsTitle);
    limitsTitleLayout->addStretch();

    mainLayout->addLayout(limitsTitleLayout);
    mainLayout->addSpacing(20);
    //---

	_actionsSetupWidget = new ActionsSetupWidget(&(mcuInData_->positionFlags), { ActionsFlag::notification, ActionsFlag::soundSignal, ActionsFlag::PCShutDown }, this);
    mainLayout->addWidget(_actionsSetupWidget);
}

PositionFrame::~PositionFrame()
{
    settings_->setValue("positionFrame/flags", _actionsSetupWidget->flags());

    settings_->setValue("positionFrame/positionXdeviation", xLimit_->value());
    settings_->setValue("positionFrame/positionYdeviation", yLimit_->value());
    settings_->setValue("positionFrame/positionZdeviation", zLimit_->value());
    settings_->sync();
}

void PositionFrame::refresh(bool isDeviceConnected)
{
    xValue_->setValue(mcuOutData_->positionSensorX);
    yValue_->setValue(mcuOutData_->positionSensorY);
    zValue_->setValue(mcuOutData_->positionSensorZ);
}
