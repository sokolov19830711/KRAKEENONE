#include "mainframe.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGridLayout>

MainFrame::MainFrame(QSharedPointer<QSettings> settings, McuInData *mcuInData, McuOutData *mcuOutData, QWidget *parent) : Frame(settings, mcuInData, mcuOutData, parent)
{ 
    QGridLayout* mainLayout = new QGridLayout;

    addMainLayout(mainLayout);

    powerStatusButton_ = new OnOffButton(this);
    powerStatusButton_->setEnabled(false);
    powerStatusButton_->setChecked(true);

    mainLayout->addWidget(new QLabel("СТАТУС ПИТАНИЯ УСТРОЙСТВА"), 0, 0, Qt::AlignRight);
    mainLayout->addWidget(powerStatusButton_, 0, 1);

    //---

    activityStatusButton_ = new OnOffButton(this);
    activityStatusButton_->setEnabled(false);
    activityStatusButton_->setChecked(true);

    mainLayout->addWidget(new QLabel("АКТИВНО | BYPASS"), 1, 0, Qt::AlignRight);
    mainLayout->addWidget(activityStatusButton_, 1, 1);

    //---

    ledIndicatorButton1_ = new OnOffButton(this);
    ledIndicatorButton1_->setEnabled(false);
    ledIndicatorButton1_->setChecked(true);

    ledIndicatorButton2_ = new OnOffButton(this);
    ledIndicatorButton2_->setEnabled(false);
    ledIndicatorButton2_->setChecked(false);

    ledIndicatorLabel_ = new QLabel(this);
    ledIndicatorLabel_->setText("встроенный | выносной");
    ledIndicatorLabel_->setStyleSheet("color:#ffc000");

    QHBoxLayout* ledIndicatorLayout = new QHBoxLayout;
    ledIndicatorLayout->setMargin(0);
    QWidget* ledIndicatorWidget = new QWidget;
    ledIndicatorWidget->setLayout(ledIndicatorLayout);
    ledIndicatorLayout->addWidget(ledIndicatorButton1_);
    ledIndicatorLayout->addWidget(ledIndicatorButton2_);
    ledIndicatorLayout->addWidget(ledIndicatorLabel_);

    mainLayout->addWidget(new QLabel("СВЕТОДИОД"), 2, 0, Qt::AlignRight);
    mainLayout->addWidget(ledIndicatorWidget, 2, 1);

    //---

    vibrationButton1_ = new OnOffButton(this);
    vibrationButton1_->setEnabled(false);
    vibrationButton1_->setChecked(true);

    vibrationButton2_ = new OnOffButton(this);
    vibrationButton2_->setEnabled(false);
    vibrationButton2_->setChecked(true);

    vibrationButton3_ = new OnOffButton(this);
    vibrationButton3_->setEnabled(false);
    vibrationButton3_->setChecked(false);

    vibrationButton4_ = new OnOffButton(this);
    vibrationButton4_->setEnabled(false);
    vibrationButton4_->setChecked(true);

    vibrationLabel_ = new QLabel(this);
    vibrationLabel_->setText("датчики 1|2|3|4");
    vibrationLabel_->setStyleSheet("color:#ffc000");

    QHBoxLayout* vibrationLayout = new QHBoxLayout;
    vibrationLayout->setMargin(0);
    QWidget* vibrationWidget = new QWidget;
    vibrationWidget->setLayout(vibrationLayout);
    vibrationLayout->addWidget(vibrationButton1_);
    vibrationLayout->addWidget(vibrationButton2_);
    vibrationLayout->addWidget(vibrationButton3_);
    vibrationLayout->addWidget(vibrationButton4_);
    vibrationLayout->addWidget(vibrationLabel_);

    mainLayout->addWidget(new QLabel("ВИБРАЦИЯ | УДАР"), 3, 0, Qt::AlignRight);
    mainLayout->addWidget(vibrationWidget, 3, 1);

    //---

    positionButton_ = new OnOffButton(this);
    positionButton_->setEnabled(false);
    positionButton_->setChecked(true);

    mainLayout->addWidget(new QLabel("ПОЛОЖЕНИЕ(ГИРОСКОП)"), 4, 0, Qt::AlignRight);
    mainLayout->addWidget(positionButton_, 4, 1);

    //---

    dustButton1_ = new OnOffButton(this);
    dustButton1_->setEnabled(false);
    dustButton1_->setChecked(true);

    dustButton2_ = new OnOffButton(this);
    dustButton2_->setEnabled(false);
    dustButton2_->setChecked(true);

    dustLabel_ = new QLabel(this);
    dustLabel_->setText("встроенный, % | выносной, %");
    dustLabel_->setStyleSheet("color:#ffc000");

    QHBoxLayout* dustLayout = new QHBoxLayout;
    dustLayout->setMargin(0);
    QWidget* dustWidget = new QWidget;
    dustWidget->setLayout(dustLayout);
    dustLayout->addWidget(dustButton1_);
    dustLayout->addWidget(dustButton2_);
    dustLayout->addWidget(dustLabel_);

    mainLayout->addWidget(new QLabel("ЗАПЫЛЕННОСТЬ"), 5, 0, Qt::AlignRight);
    mainLayout->addWidget(dustWidget, 5, 1);

    //---

    moistureLabel_ = new QLabel(this);
    moistureLabel_->setText("значение, %");
    moistureLabel_->setStyleSheet("color:#ffc000");

    moistureButton_ = new OnOffButton(this);
    moistureButton_->setEnabled(false);
    moistureButton_->setChecked(true);

    QHBoxLayout* moistureLayout = new QHBoxLayout;
    moistureLayout->setMargin(0);
    QWidget* moistureWidget = new QWidget;
    moistureWidget->setLayout(moistureLayout);
    moistureLayout->addWidget(moistureButton_);
    moistureLayout->addWidget(moistureLabel_);

    mainLayout->addWidget(new QLabel("ВЛАЖНОСТЬ"), 6, 0, Qt::AlignRight);
    mainLayout->addWidget(moistureWidget, 6, 1);

    //---

    temperatureButton1_ = new OnOffButton(this);
    temperatureButton1_->setEnabled(false);
    temperatureButton1_->setChecked(true);

    temperatureButton2_ = new OnOffButton(this);
    temperatureButton2_->setEnabled(false);
    temperatureButton2_->setChecked(true);

    temperatureButton3_ = new OnOffButton(this);
    temperatureButton3_->setEnabled(false);
    temperatureButton3_->setChecked(true);

    temperatureLabel_ = new QLabel(this);
    temperatureLabel_->setText("датчики 1|2|3");
    temperatureLabel_->setStyleSheet("color:#ffc000");

    QHBoxLayout* temperatureLayout = new QHBoxLayout;
    temperatureLayout->setMargin(0);
    QWidget* temperatureWidget = new QWidget;
    temperatureWidget->setLayout(temperatureLayout);
    temperatureLayout->addWidget(temperatureButton1_);
    temperatureLayout->addWidget(temperatureButton2_);
    temperatureLayout->addWidget(temperatureButton3_);
    temperatureLayout->addWidget(temperatureLabel_);

    mainLayout->addWidget(new QLabel("ТЕМПЕРАТУРА"), 7, 0, Qt::AlignRight);
    mainLayout->addWidget(temperatureWidget, 7, 1);

    //---

    breakInButton1_ = new OnOffButton(this);
    breakInButton1_->setEnabled(false);
    breakInButton1_->setChecked(true);
    breakInButton1_->setAlert();

    breakInButton2_ = new OnOffButton(this);
    breakInButton2_->setEnabled(false);
    breakInButton2_->setChecked(true);

    breakInButton3_ = new OnOffButton(this);
    breakInButton3_->setEnabled(false);
    breakInButton3_->setChecked(true);

    breakInButton4_ = new OnOffButton(this);
    breakInButton4_->setEnabled(false);
    breakInButton4_->setChecked(true);

    breakInLabel_ = new QLabel(this);
    breakInLabel_->setText("датчики 1|2|3|4");
    breakInLabel_->setStyleSheet("color:#ffc000");

    QHBoxLayout* breakInLayout = new QHBoxLayout;
    breakInLayout->setMargin(0);
    QWidget* breakInWidget = new QWidget;
    breakInWidget->setLayout(breakInLayout);
    breakInLayout->addWidget(breakInButton1_);
    breakInLayout->addWidget(breakInButton2_);
    breakInLayout->addWidget(breakInButton3_);
    breakInLayout->addWidget(breakInButton4_);
    breakInLayout->addWidget(breakInLabel_);

    mainLayout->addWidget(new QLabel("ВСКРЫТИЕ"), 8, 0, Qt::AlignRight);
    mainLayout->addWidget(breakInWidget, 8, 1);

    //---

    iButtonButton_ = new OnOffButton(this);
    iButtonButton_->setEnabled(false);
    iButtonButton_->setChecked(true);

    mainLayout->addWidget(new QLabel("МОДУЛЬ IBUTTON"), 9, 0, Qt::AlignRight);
    mainLayout->addWidget(iButtonButton_, 9, 1);
}
