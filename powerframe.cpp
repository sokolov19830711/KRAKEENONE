#include "powerframe.h"

#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>

PowerFrame::PowerFrame(QSharedPointer<QSettings> settings, McuInData *mcuInData, McuOutData *mcuOutData, QWidget *parent) : Frame(settings, mcuInData, mcuOutData, parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout;
    addMainLayout(mainLayout);

    QFormLayout* leftLayout = new QFormLayout;
    mainLayout->addLayout(leftLayout);

    mainLayout->addSpacing(40);

    QFormLayout* rightLayout = new QFormLayout;
    mainLayout->addLayout(rightLayout);

    //---

    QLabel* resetSettingsLabel = new QLabel("ВЫБЕРИТЕ СПОСОБ ПОЛНОГО СБРОСА УСТРОЙСТВА\nПРИ ВЫКЛЮЧЕННОМ ПК (кнопкой RST)");
    resetSettingsLabel->setAlignment(Qt::AlignCenter);
    QHBoxLayout* resetSettingsLabelLayout = new QHBoxLayout;
    resetSettingsLabelLayout->addStretch();
    resetSettingsLabelLayout->addWidget(resetSettingsLabel);
    resetSettingsLabelLayout->addStretch();
    leftLayout->addRow(resetSettingsLabelLayout);

    resetSettingsButtons_ = new ButtonGroup({"удержать\nRST\n60 сек", "удержать\nRST\n10 сек", "нажать\nRST\n3 + 5 раза", "нажать\nRST\n3 + 5 раза"}, 60, 60, this);
    leftLayout->addRow(resetSettingsButtons_);

    QLabel* resetExampleLabel = new QLabel("пример: нажать 3 раза RST, дождаться\nтрехкратного зажигания светодиода,\nнажать еще 3 раза RST)");
    resetExampleLabel->setStyleSheet("font-size:7pt; font:italic; color:#ffc000");
    QHBoxLayout* resetExampleLabelLayout = new QHBoxLayout;
    resetExampleLabelLayout->addStretch();
    resetExampleLabelLayout->addWidget(resetExampleLabel);
    leftLayout->addRow(resetExampleLabelLayout);

    //---

    leftLayout->addRow(new QLabel);
    leftLayout->addRow(new QLabel);

    QLabel* blockHDDSettingsLabel = new QLabel("ВЫБЕРИТЕ СПОСОБ СБРОСА БЛОКИРОВКИ HDD\nПРИ ВЫКЛЮЧЕННОМ ПК (кнопкой RST)");
    blockHDDSettingsLabel->setAlignment(Qt::AlignCenter);
    QHBoxLayout* blockHDDSettingsLabelLayout = new QHBoxLayout;
    blockHDDSettingsLabelLayout->addStretch();
    blockHDDSettingsLabelLayout->addWidget(blockHDDSettingsLabel);
    blockHDDSettingsLabelLayout->addStretch();
    leftLayout->addRow(blockHDDSettingsLabelLayout);

    blockHDDSettingsButtons_ = new ButtonGroup({"удержать\nRST\n60 сек", "удержать\nRST\n10 сек", "нажать\nRST\n3 + 5 раза", "нажать\nRST\n3 + 5 раза"}, 60, 60, this);
    leftLayout->addRow(blockHDDSettingsButtons_);

    QLabel* blockHDDExampleLabel = new QLabel("пример: нажать 3 раза RST, дождаться\nтрехкратного зажигания светодиода,\nнажать еще 3 раза RST)");
    blockHDDExampleLabel->setStyleSheet("font-size:7pt; font:italic; color:#ffc000");
    QHBoxLayout* blockHDDExampleLabelLayout = new QHBoxLayout;
    blockHDDExampleLabelLayout->addStretch();
    blockHDDExampleLabelLayout->addWidget(blockHDDExampleLabel);
    leftLayout->addRow(blockHDDExampleLabelLayout);

    //---

    powerButtonActiveButton_ = new OnOffButton;
    rightLayout->addRow("ДОСТУПНОСТЬ КНОПКИ PWR НА КОРПУСЕ", powerButtonActiveButton_);

    resetButtonActiveButton_ = new OnOffButton;
    rightLayout->addRow("ДОСТУПНОСТЬ КНОПКИ RESET НА КОРПУСЕ", resetButtonActiveButton_);

    powerByPasswordButton_ = new OnOffButton;
    rightLayout->addRow("ВКЛЮЧЕНИЕ ПК МЕТОДОМ ПАРОЛЯ\nНА КНОПКАХ PWR | RST", powerByPasswordButton_);

    rightLayout->addRow(new QLabel);

    //---

    QLabel* powerSettingsLabel = new QLabel("ВЫБЕРИТЕ СПОСОБ ВКЛЮЧЕНИЯ ПК\nКНОПКАМИ PWR | RST");
    powerSettingsLabel->setAlignment(Qt::AlignCenter);
    QHBoxLayout* powerSettingsLabelLayout = new QHBoxLayout;
    powerSettingsLabelLayout->addStretch();
    powerSettingsLabelLayout->addWidget(powerSettingsLabel);
    powerSettingsLabelLayout->addStretch();
    rightLayout->addRow(powerSettingsLabelLayout);

    powerSettingsButtons_ = new ButtonGroup({"удержать\nPWR + RST\n3 сек", "удержать\nPWR\n7 сек", "нажать\nPWR\n5 раз", "нажать\nPWR\n3 раза"}, 60, 60, this);
    rightLayout->addRow(powerSettingsButtons_);

    //---

    QHBoxLayout* blockingTimeLayout = new QHBoxLayout;
    blockingTime_ = new SpinBox;
    blockingTime_->setValueFieldWidth(30);
    blockingTimeLayout->addWidget(new QLabel("БЛОКИРОВАТЬ ПРИ ПОПЫТКЕ\nПОДБОРА КОМБИНАЦИИ, МИН"));
    blockingTimeLayout->addStretch();
    blockingTimeLayout->addWidget(blockingTime_);
    rightLayout->addRow(blockingTimeLayout);

    //---

    QHBoxLayout* notResponseResetLayout = new QHBoxLayout;
    notResponseResetLayout->addWidget(new QLabel("ПЕРЕЗАГРУЗКА ПРИ\nЗАВИСАНИИ ПК"));
    notResponseResetButton_ = new OnOffButton;
    notResponseResetLayout->addWidget(notResponseResetButton_);
    notResponseResetLayout->addWidget(new QLabel("ЧЕРЕЗ, МИН"));
    notResponseResetTime_ = new SpinBox;
    notResponseResetTime_->setValueFieldWidth(30);
    notResponseResetLayout->addWidget(notResponseResetTime_);
    rightLayout->addRow(notResponseResetLayout);
}

PowerFrame::~PowerFrame()
{

}

void PowerFrame::refresh()
{

}

void PowerFrame::setControlsEnabled(bool state)
{
    resetSettingsButtons_->setEnabled(state);
    blockHDDSettingsButtons_->setEnabled(state);
    powerSettingsButtons_->setEnabled(state);

    powerButtonActiveButton_->setEnabled(state);
    resetButtonActiveButton_->setEnabled(state);
    powerByPasswordButton_->setEnabled(state);

    blockingTime_->setEnabled(state);

    notResponseResetButton_->setEnabled(state);
    notResponseResetTime_->setEnabled(state);
}
