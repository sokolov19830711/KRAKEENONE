#include "ibuttonframe.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>

IButtonFrame::IButtonFrame(QSharedPointer<QSettings> settings, McuInData *mcuInData, McuOutData *mcuOutData, QWidget *parent) : Frame(settings, mcuInData, mcuOutData, parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout;
    addMainLayout(mainLayout);

    QFormLayout* leftLayout = new QFormLayout;
    leftLayout->setSpacing(12);
    leftLayout->setLabelAlignment(Qt::AlignRight);
    leftLayout->setFormAlignment(Qt::AlignCenter);
    mainLayout->addLayout(leftLayout);

    turnOnButton_ = new OnOffButton;
	connect(turnOnButton_, &OnOffButton::toggled, [=]() {setBit(mcuInData->iButtonFlags, IButtonFlag::iButtonActive, turnOnButton_->isChecked()); });
    turnOnButton_->setChecked(mcuInData->iButtonFlags & IButtonFlag::iButtonActive);
    QLabel* turnOnLabel = new QLabel("Модуль IButton активен");
    turnOnLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    leftLayout->addRow(turnOnLabel, turnOnButton_);

    lockPWRButtonButton_ = new OnOffButton;
    lockPWRButtonButton_->setChecked(!mcuInData_->isPWRavaliable);
    connect(lockPWRButtonButton_, &OnOffButton::toggled, [=]() {mcuInData_->isPWRavaliable = !lockPWRButtonButton_->isChecked(); });
	QLabel* lockPWRButtonLabel = new QLabel("Заблокировать кнопку включения ПК");
    lockPWRButtonLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    leftLayout->addRow(lockPWRButtonLabel, lockPWRButtonButton_);

    resetButton_ = new OnOffButton;
	connect(resetButton_, &OnOffButton::toggled, [=]() {setBit(mcuInData->iButtonFlags, IButtonFlag::reset, resetButton_->isChecked()); });
    resetButton_->setChecked(mcuInData->iButtonFlags & IButtonFlag::reset);
	QLabel* lockResetLabel = new QLabel("Перезагрузка ПК в случае\nиспользования стороннего ключа");
    lockResetLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    leftLayout->addRow(lockResetLabel, resetButton_);

    powerOffButton_ = new OnOffButton;
	connect(powerOffButton_, &OnOffButton::toggled, [=]() {setBit(mcuInData->iButtonFlags, IButtonFlag::shutDown, powerOffButton_->isChecked()); });
    powerOffButton_->setChecked(mcuInData->iButtonFlags & IButtonFlag::shutDown);
	QLabel* powerOffLabel = new QLabel("Выключение ПК в случае\nиспользования стороннего ключа");
    powerOffLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    leftLayout->addRow(powerOffLabel, powerOffButton_);

    leftLayout->addRow(new QLabel);

    setupNewUserKeyButton_ = new QPushButton("ПРИВЯЗАТЬ НОВЫЙ\nКЛЮЧ ПОЛЬЗОВАТЕЛЯ");
    setupNewUserKeyButton_->setFixedHeight(32);
    leftLayout->addRow(setupNewUserKeyButton_);

    setupNewAdminKeyButton_ = new QPushButton("ПРИВЯЗАТЬ НОВЫЙ\nКЛЮЧ АДМИНИСТРАТОРА");
    setupNewAdminKeyButton_->setFixedHeight(32);
    leftLayout->addRow(setupNewAdminKeyButton_);

    QVBoxLayout* rightLayout = new QVBoxLayout;
    mainLayout->addLayout(rightLayout);

    rightLayout->setSpacing(0);
    rightLayout->setMargin(0);
    rightLayout->addSpacing(92);

    QHBoxLayout* invalidKeyUsageCountToResetLayout = new QHBoxLayout;
    rightLayout->addLayout(invalidKeyUsageCountToResetLayout);

    invalidKeyUsageCountToReset_ = new SpinBox;
    invalidKeyUsageCountToResetLayout->addWidget(new QLabel("БОЛЕЕ ЧЕМ"));
    invalidKeyUsageCountToResetLayout->addWidget(invalidKeyUsageCountToReset_);
    invalidKeyUsageCountToResetLayout->addWidget(new QLabel("РАЗ ПОДРЯД"));

    QHBoxLayout* invalidKeyUsageCountToTurnOffLayout = new QHBoxLayout;
    rightLayout->addLayout(invalidKeyUsageCountToTurnOffLayout);

    invalidKeyUsageCountToTurnOff_ = new SpinBox;
    invalidKeyUsageCountToTurnOffLayout->addWidget(new QLabel("БОЛЕЕ ЧЕМ"));
    invalidKeyUsageCountToTurnOffLayout->addWidget(invalidKeyUsageCountToTurnOff_);
    invalidKeyUsageCountToTurnOffLayout->addWidget(new QLabel("РАЗ ПОДРЯД"));

    rightLayout->addStretch();
}

IButtonFrame::~IButtonFrame()
{
    settings_->setValue("iButtonFrame/flags", mcuInData_->iButtonFlags);
}

void IButtonFrame::refresh(bool isDeviceConnected)
{
    lockPWRButtonButton_->setChecked(!mcuInData_->isPWRavaliable);
}
