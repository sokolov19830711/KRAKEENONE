#include "runninghoursframe.h"

#include <QDebug>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>

#ifdef Q_OS_WIN32
#include <windows.h>
#endif

RunningHoursFrame::RunningHoursFrame(QSharedPointer<QSettings> settings, McuInData *mcuInData, McuOutData *mcuOutData, QWidget *parent) : Frame(settings, mcuInData, mcuOutData, parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    addMainLayout(mainLayout);

    QHBoxLayout* timeLayout = new QHBoxLayout;

    mainLayout->addLayout(timeLayout);

    QVBoxLayout* deviceLayout = new QVBoxLayout;
    timeLayout->addLayout(deviceLayout);

    timeLayout->addSpacing(70);

    QVBoxLayout* pcLayout = new QVBoxLayout;
    timeLayout->addLayout(pcLayout);

    //---

    deviceLayout->addWidget(new QLabel("ВРЕМЯ РАБОТЫ УСТРОЙСТВА"));
    deviceLayout->addSpacing(20);

    QLabel* sumDeviceLabel = new QLabel("СУММАРНОЕ:");
    sumDeviceLabel->setStyleSheet("font:italic; color:#ffc000");
    deviceLayout->addWidget(sumDeviceLabel);

    sumDeviceTime_ = new QLabel("0");
    sumDeviceTime_->setStyleSheet("font-size : 14pt");
    deviceLayout->addWidget(sumDeviceTime_);

    deviceLayout->addSpacing(20);

    QLabel* sessionDeviceLabel = new QLabel("ЗА СЕССИЮ:");
    sessionDeviceLabel->setStyleSheet("font:italic; color:#ffc000");
    deviceLayout->addWidget(sessionDeviceLabel);

    sessionDeviceTime_ = new QLabel("0");
    sessionDeviceTime_->setStyleSheet("font-size : 14pt");
    deviceLayout->addWidget(sessionDeviceTime_);

    //---

    pcLayout->addWidget(new QLabel("ВРЕМЯ РАБОТЫ ПК"));
    pcLayout->addSpacing(20);

    QLabel* sumPcLabel = new QLabel("СУММАРНОЕ:");
    sumPcLabel->setStyleSheet("font:italic; color:#ffc000");
    pcLayout->addWidget(sumPcLabel);

    sumPcTime_ = new QLabel("0");
    sumPcTime_->setStyleSheet("font-size : 14pt");
    pcLayout->addWidget(sumPcTime_);

    pcLayout->addSpacing(20);

    QLabel* sessionPcLabel = new QLabel("ЗА СЕССИЮ:");
    sessionPcLabel->setStyleSheet("font:italic; color:#ffc000");
    pcLayout->addWidget(sessionPcLabel);

    sessionPcTime_ = new QLabel("0");
    sessionPcTime_->setStyleSheet("font-size : 14pt");
    pcLayout->addWidget(sessionPcTime_);

    //---

    QHBoxLayout* exportLogButtonLayout = new QHBoxLayout;

    exportLogButton_ = new QPushButton("ЖУРНАЛ СОБЫТИЙ");
    exportLogButton_->setFixedSize(120, 30);
    exportLogButton_->setToolTip("Выгрузить журнал событий в файл PDF");

    exportLogButtonLayout->addWidget(exportLogButton_);

    mainLayout->addSpacing(20);
    mainLayout->addLayout(exportLogButtonLayout);
    mainLayout->addSpacing(20);

    //---

    QFormLayout* batteryLayout = new QFormLayout;
    mainLayout->addLayout(batteryLayout);

    builtInBatteryState_ = new QLabel("НЕ ПОДКЛЮЧЕНА");
    builtInBatteryState_->setStyleSheet("color:#c05046");

    externBatteryState_ = new QLabel("НЕ ПОДКЛЮЧЕНА");
    externBatteryState_->setStyleSheet("color:#c05046");

    batteryLayout->addRow("Встроенная АКБ", builtInBatteryState_);
    batteryLayout->addRow("Внешняя АКБ", externBatteryState_);
}

RunningHoursFrame::~RunningHoursFrame()
{

}

void RunningHoursFrame::refresh(bool isDeviceConnected)
{
    QTime time(0, 0);

    sessionDeviceTime_->setText(time.addSecs(mcuOutData_->sessionRunningTime).toString("hh ч mm мин ss сек"));

#ifdef Q_OS_WIN32
	auto elapsedTime = std::chrono::milliseconds(GetTickCount64()).count() / 1000;
    sessionPcTime_->setText(time.addSecs(elapsedTime).toString("hh ч mm мин ss сек"));
#endif

    sumDeviceTime_->setText(time.addSecs(mcuOutData_->totalRunningTime).toString("hh ч mm мин"));

    sumPcTime_->setText(time.addSecs(settings_->value("OS_totalRunningTime").toUInt()).toString("hh ч mm мин"));
}


