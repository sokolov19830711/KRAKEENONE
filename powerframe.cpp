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

    mainLayout->addSpacing(20);

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

	QString settingsButtonsStyle = "QPushButton{height : 75; width : 60; color: #ffffff; border-style:none; border-color:#7f7f7f; background-color:#595959;}"
		                           "QPushButton:checked{font : bold; color: #ffffff; border-style:none; border-color:#7f7f7f; background-color:#00b050;}";

    QStringList resetSettingsButtonsTextes = { "удержать\nRST\n60 сек", "удержать\nRST\n10 сек", "нажать\nRST\n3 + 5 раза", "нажать\nRST\n3 + 5 раза" };
    resetSettingsButtons_ = new SwitchButtonsWidget(1, 4, settingsButtonsStyle, resetSettingsButtonsTextes, this);
    resetSettingsButtons_->setSpacing(5);
    leftLayout->addRow(resetSettingsButtons_);

    //---

    leftLayout->addRow(new QLabel);

    QLabel* blockHDDSettingsLabel = new QLabel("ВЫБЕРИТЕ СПОСОБ СБРОСА БЛОКИРОВКИ HDD\nПРИ ВЫКЛЮЧЕННОМ ПК (кнопкой RST)");
    blockHDDSettingsLabel->setAlignment(Qt::AlignCenter);
    QHBoxLayout* blockHDDSettingsLabelLayout = new QHBoxLayout;
    blockHDDSettingsLabelLayout->addStretch();
    blockHDDSettingsLabelLayout->addWidget(blockHDDSettingsLabel);
    blockHDDSettingsLabelLayout->addStretch();
    leftLayout->addRow(blockHDDSettingsLabelLayout);

	
    QStringList blockHDDSettingsButtonsTextes = { "удержать\nRST\n60 сек", "удержать\nRST\n10 сек", "нажать\nRST\n3 + 5 раза", "нажать\nRST\n3 + 5 раза" };
    blockHDDSettingsButtons_ = new SwitchButtonsWidget(1, 4, settingsButtonsStyle, blockHDDSettingsButtonsTextes, this);
    blockHDDSettingsButtons_->setSpacing(5);
    leftLayout->addRow(blockHDDSettingsButtons_);

    //---

    leftLayout->addRow(new QLabel);

    powerButtonActiveButton_ = new OnOffButton;
    powerButtonActiveButton_->setChecked(settings_->value("PWR/isPWRavaliable").toBool());
    connect(powerButtonActiveButton_, &OnOffButton::toggled, [=]() {mcuInData_->isPWRavaliable = powerButtonActiveButton_->isChecked(); });
    leftLayout->addRow("ДОСТУПНОСТЬ КНОПКИ PWR НА КОРПУСЕ", powerButtonActiveButton_);

    resetButtonActiveButton_ = new OnOffButton;
    resetButtonActiveButton_->setChecked(settings_->value("PWR/isRSTavaliable").toBool());
    connect(resetButtonActiveButton_, &OnOffButton::toggled, [=]() {mcuInData_->isRSTavaliable = resetButtonActiveButton_->isChecked(); });
    leftLayout->addRow("ДОСТУПНОСТЬ КНОПКИ RESET НА КОРПУСЕ", resetButtonActiveButton_);

    powerByPasswordButton_ = new OnOffButton;
    leftLayout->addRow("ВКЛЮЧЕНИЕ ПК МЕТОДОМ ПАРОЛЯ\nНА КНОПКАХ PWR | RST", powerByPasswordButton_);

    //---

    QLabel* powerSettingsLabel = new QLabel("УКАЖИТЕ УОВЕНЬ ЗАЩИТЫ\n(КОДИРОВАНИЕ КНОПКИ PWR)");
    powerSettingsLabel->setAlignment(Qt::AlignCenter);
    QHBoxLayout* powerSettingsLabelLayout = new QHBoxLayout;
    powerSettingsLabelLayout->addStretch();
    powerSettingsLabelLayout->addWidget(powerSettingsLabel);
    powerSettingsLabelLayout->addStretch();
    rightLayout->addRow(powerSettingsLabelLayout);
    rightLayout->addRow(new QLabel);

	QString buttonsStyle = "QPushButton{height : 40; width : 80; color: #ffffff; border-style:none; border-color:#7f7f7f; background-color:#595959;}"
		"QPushButton:checked{font : bold; color: #ffffff; border-style:none; border-color:#7f7f7f; background-color:#00b050;}";

	pwswStatePanel_ = new SwitchButtonsWidget(1, 4, buttonsStyle, { "НИЗКИЙ", "СРЕДНИЙ", "ВЫСОКИЙ", "OFF" }, this);
	pwswStatePanel_->setChecked(settings_->value("pwswLevel").toInt());
	pwswStatePanel_->setSpacing(5);
	pwswStatePanel_->setButtonStyleSheet(0, "QPushButton:checked{ font: bold; color: #ffffff; border-style:none; border-color:#7f7f7f; background-color:#c05046; }");
	pwswStatePanel_->setButtonStyleSheet(1, "QPushButton:checked{ font: bold; color: #ffffff; border-style:none; border-color:#7f7f7f; background-color:#ffb814; }");
	pwswStatePanel_->setButtonStyleSheet(3, "QPushButton:checked{ font: bold; color: #ffffff; border-style:none; border-color:#7f7f7f; background-color:#c05046; }");
    rightLayout->addRow(pwswStatePanel_);

    int powerButtonPwdLevel = settings_->value("PWR/powerButtonPwdLevel").toInt();
    if (powerButtonPwdLevel == 0)
    {
        pwswStatePanel_->setChecked(3);
    }
    else
    {
        pwswStatePanel_->setChecked(powerButtonPwdLevel - 1);
    }

	connect(pwswStatePanel_, &SwitchButtonsWidget::idClicked,
		[=]()
		{
			if (pwswStatePanel_->checkedId() == 3)
			{
				mcuInData_->powerButtonPwdLevel = 0;
			}
			else
			{
				mcuInData_->powerButtonPwdLevel = pwswStatePanel_->checkedId() + 1;
			}
		});

    //---

    QHBoxLayout* blockingTimeLayout = new QHBoxLayout;
    blockingTime_ = new SpinBox;
    blockingTime_->setValueFieldWidth(30);
    blockingTimeLayout->addWidget(new QLabel("БЛОКИРОВАТЬ ПРИ ПОПЫТКЕ\nПОДБОРА КОМБИНАЦИИ, МИН"));
    blockingTimeLayout->addStretch();
    blockingTimeLayout->addWidget(blockingTime_);
    rightLayout->addRow(blockingTimeLayout);

	//---

	QHBoxLayout* inputPeriodLayout = new QHBoxLayout;
	inputPeriod_ = new SpinBox;
    inputPeriod_->setValueFieldWidth(30);
    inputPeriod_->setValue(settings_->value("PWR/digitInputPeriod").toInt());
    inputPeriodLayout->addWidget(new QLabel("ВРЕМЯ ОЖИДАНИЯ ВВОДА\nРАЗРЯДА КОМБИНАЦИИ, СЕК"));
    inputPeriodLayout->addStretch();
    inputPeriodLayout->addWidget(inputPeriod_);
	rightLayout->addRow(inputPeriodLayout);

    connect(inputPeriod_, &SpinBox::valueChanged, [=]() {mcuInData_->digitInputPeriod = inputPeriod_->value(); });

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

    //---

    rightLayout->addRow(new QLabel);

	QLabel* digitsLabel = new QLabel("ВЫБЕРИТЕ ЧИСЛО КОМБИНАЦИИ");
    digitsLabel->setAlignment(Qt::AlignCenter);
	QHBoxLayout* digitsLabelLayout = new QHBoxLayout;
    digitsLabelLayout->addStretch();
    digitsLabelLayout->addWidget(digitsLabel);
    digitsLabelLayout->addStretch();
	rightLayout->addRow(digitsLabelLayout);
	rightLayout->addRow(new QLabel);

	QHBoxLayout* combinationLayout = new QHBoxLayout;
    rightLayout->addRow(combinationLayout);

	QString digitButtonsStyle = "QPushButton{height : 30; width : 20; color: #ffffff; border-style:none; border-color:#7f7f7f; background-color:#595959;}"
		"QPushButton:checked{font : bold; color: #ffffff; border-style:none; border-color:#7f7f7f; background-color:#00b050;}";

	digit1_ = new SwitchButtonsWidget(3, 3, digitButtonsStyle, { "1", "2", "3", "4", "5", "6", "7", "8", "9" }, this);
	digit1_->setSpacing(3);
	digit1_->setChecked(settings_->value("PWR/digit1").toInt() - 1);
	combinationLayout->addWidget(digit1_);
	combinationLayout->addSpacing(10);



    connect(digit1_, &SwitchButtonsWidget::idClicked, [=]()
        {
            mcuInData_->powerButtonPwdDigit1 = digit1_->checkedId() + 1;
        });

	digit2_ = new SwitchButtonsWidget(3, 3, digitButtonsStyle, { "1", "2", "3", "4", "5", "6", "7", "8", "9" }, this);
	digit2_->setSpacing(3);
	digit2_->setChecked(settings_->value("PWR/digit2").toInt() - 1);
	combinationLayout->addWidget(digit2_);
	combinationLayout->addSpacing(10);

	connect(digit2_, &SwitchButtonsWidget::idClicked, [=]()
		{
			mcuInData_->powerButtonPwdDigit2 = digit2_->checkedId() + 1;
		});

	digit3_ = new SwitchButtonsWidget(3, 3, digitButtonsStyle, { "1", "2", "3", "4", "5", "6", "7", "8", "9" }, this);
	digit3_->setSpacing(3);
	digit3_->setChecked(settings_->value("PWR/digit3").toInt() - 1);
	combinationLayout->addWidget(digit3_);

	connect(digit3_, &SwitchButtonsWidget::idClicked, [=]()
		{
			mcuInData_->powerButtonPwdDigit3 = digit3_->checkedId() + 1;
		});
}

PowerFrame::~PowerFrame()
{
    if(pwswStatePanel_->checkedId() == 3)
    {
        settings_->setValue("PWR/powerButtonPwdLevel", 0);
    }
    else
    {
        settings_->setValue("PWR/powerButtonPwdLevel", pwswStatePanel_->checkedId() + 1);
    }

    settings_->setValue("PWR/digit1", digit1_->checkedId() + 1);
    settings_->setValue("PWR/digit2", digit2_->checkedId() + 1);
    settings_->setValue("PWR/digit3", digit3_->checkedId() + 1);

    settings_->setValue("PWR/digitInputPeriod", inputPeriod_->value());

    settings_->setValue("PWR/isPWRavaliable", powerButtonActiveButton_->isChecked());
    settings_->setValue("PWR/isRSTavaliable", resetButtonActiveButton_->isChecked());
}

void PowerFrame::refresh(bool isDeviceConnected)
{

}
