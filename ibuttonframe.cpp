#include "ibuttonframe.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>

IButtonFrame::IButtonFrame(QSharedPointer<QSettings> settings, McuInData *mcuInData, McuOutData *mcuOutData, QWidget *parent) : Frame(settings, mcuInData, mcuOutData, parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout;
    addMainLayout(mainLayout);

    QFormLayout* leftLayout = new QFormLayout;
    leftLayout->setLabelAlignment(Qt::AlignRight);
    leftLayout->setFormAlignment(Qt::AlignCenter);
    mainLayout->addLayout(leftLayout);

    turnOnButton_ = new OnOffButton;
    leftLayout->addRow("Модуль IButton активен", turnOnButton_);

    lockPWRButtonButton_ = new OnOffButton;
    leftLayout->addRow("Заблокировать кнопку включения ПК", lockPWRButtonButton_);

    resetButton_ = new OnOffButton;
    leftLayout->addRow("Перезагрузка ПК в случае\nиспользования стороннего ключа", resetButton_);

    powerOffButton_ = new OnOffButton;
    leftLayout->addRow("Выключение ПК в случае\nиспользования стороннего ключа", powerOffButton_);

    leftLayout->addRow(new QLabel);

    setupNewUserKeyButton_ = new QPushButton("ПРИВЯЗАТЬ НОВЫЙ\nКЛЮЧ ПОЛЬЗОВАТЕЛЯ");
    leftLayout->addRow(setupNewUserKeyButton_);

    setupNewAdminKeyButton_ = new QPushButton("ПРИВЯЗАТЬ НОВЫЙ\nКЛЮЧ АДМИНИСТРАТОРА");
    leftLayout->addRow(setupNewAdminKeyButton_);

    QVBoxLayout* rightLayout = new QVBoxLayout;
    mainLayout->addLayout(rightLayout);

    rightLayout->setSpacing(0);
    rightLayout->addSpacing(58);

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

}

void IButtonFrame::refresh(bool isDeviceConnected)
{

}
