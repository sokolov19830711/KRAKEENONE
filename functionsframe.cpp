#include "functionsframe.h"

#include <QSerialPortInfo>
#include <QFormLayout>
#include <QAbstractItemView>

#include <QDebug>

FunctionsFrame::FunctionsFrame(QSharedPointer<QSettings> settings, McuInData *mcuInData, McuOutData *mcuOutData, const QString &serialPortName, QWidget *parent)
    : Frame(settings, mcuInData, mcuOutData, parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout;
    addMainLayout(mainLayout);

    QFormLayout* rightLayout = new QFormLayout;
    mainLayout->addLayout(rightLayout);

    //---

    avaliableSerialPorts_ = new QComboBox(this);
    avaliableSerialPorts_->setStyleSheet("QComboBox {height : 30px; min-width : 50px; border: 0px; font-size : 10pt} QFrame { border: 0px;}");

    auto ports = QSerialPortInfo::availablePorts();
    for(auto & i : ports)
    {
        avaliableSerialPorts_->addItem(i.portName());
    }
    avaliableSerialPorts_->setCurrentText(serialPortName);
    rightLayout->addRow("ПОДКЛЮЧЕНИЕ ЧЕРЕЗ", avaliableSerialPorts_);

    //---

    startOnBootButton_ = new OnOffButton(this);
    connect(startOnBootButton_, &OnOffButton::toggled, [=]() {setBit(mcuInData->functionsFlags, FunctionsFlag::startOnBoot, startOnBootButton_->isChecked()); });
    startOnBootButton_->setChecked(mcuInData->functionsFlags & FunctionsFlag::startOnBoot);
    rightLayout->addRow("АВТОМАТИЧЕСКИЙ ЗАПУСК ПРИ ЗАГРУЗКЕ\nОПЕРАЦИОННОЙ СИСТЕМЫ", startOnBootButton_);

    //---

    lockOSButton_ = new OnOffButton(this);
    connect(lockOSButton_, &OnOffButton::toggled, [=](){setBit(mcuInData->functionsFlags, FunctionsFlag::lockOS, lockOSButton_->isChecked());});
    lockOSButton_->setChecked(mcuInData->functionsFlags & FunctionsFlag::lockOS);
    rightLayout->addRow("БЛОКИРОВАТЬ КОМПЮТЕР ЕСЛИ\nУСТРОЙСТВО ОТКЛЮЧЕНО", lockOSButton_);

    //---

    lockAppButton_ = new OnOffButton(this);
    connect(lockAppButton_, &OnOffButton::toggled, [=](){setBit(mcuInData->functionsFlags, FunctionsFlag::lockApp, lockAppButton_->isChecked());});
    lockAppButton_->setChecked(mcuInData->functionsFlags & FunctionsFlag::lockApp);
    rightLayout->addRow("БЛОКИРОВАТЬ ПРИЛОЖЕНИЕ ПОСЛЕ ТРЕХ\nПОПЫТОК ВВОДА ПАРОЛЯ", lockAppButton_);

    //---

    turnOnButton_ = new OnOffButton(this);
    connect(turnOnButton_, &OnOffButton::toggled, [=](){setBit(mcuInData->functionsFlags, FunctionsFlag::turnOn, turnOnButton_->isChecked());});
    turnOnButton_->setChecked(mcuInData->functionsFlags & FunctionsFlag::turnOn);
    rightLayout->addRow("ВКЛЮЧИТЬ / ВЫКЛЮЧИТЬ УСТРОЙСТВО", turnOnButton_);

    //---

    QFormLayout* leftLayout = new QFormLayout;
    mainLayout->addSpacing(50);
    mainLayout->addLayout(leftLayout);

    notificationLabel_ = new QLabel(this);
    notificationLabel_->setText("НАСТРОЙКА УВЕДОМЛЕНИЙ");
    leftLayout->addRow(notificationLabel_);

    //---

    serverName_ = new QLineEdit(this);
    serverName_->setToolTip("ПРИМЕР: smtp.mail.ru");
    serverName_->setStyleSheet("font-size:10pt");
    serverName_->setAlignment(Qt::AlignCenter);
    serverName_->setFixedSize(250, 25);
    serverName_->setText(settings_->value("SMTP/server").toString());

    leftLayout->addRow("СЕРВЕР", serverName_);

    //---

    portName_ = new QLineEdit(this);
    portName_->setToolTip("ПРИМЕР: 465");
    portName_->setStyleSheet("font-size:10pt");
    portName_->setAlignment(Qt::AlignCenter);
    portName_->setFixedSize(100, 25);
    portName_->setText(settings_->value("SMTP/port").toString());

    sslLabel_ = new QLabel(this);
    sslLabel_->setText("Использовать SSL");

    sslButton_ = new OnOffButton(this);
    sslButton_->setChecked(settings_->value("SMTP/ssl").toBool());

    QHBoxLayout* portAndSslLayout = new QHBoxLayout;
    portAndSslLayout->addWidget(portName_);
    portAndSslLayout->addStretch();
    portAndSslLayout->addWidget(sslLabel_);
    portAndSslLayout->addWidget(sslButton_);

    leftLayout->addRow("ПОРТ", portAndSslLayout);

    //---

    userName_ = new QLineEdit(this);
    userName_->setStyleSheet("font-size:10pt");
    userName_->setAlignment(Qt::AlignCenter);
    userName_->setFixedSize(250, 25);
    userName_->setText(settings_->value("SMTP/user").toString());

    leftLayout->addRow("ПОЛЬЗОВАТЕЛЬ", userName_);

    //---

    smtpPassword_ = new QLineEdit(this);
    smtpPassword_->setStyleSheet("font-size:10pt");
    smtpPassword_->setAlignment(Qt::AlignCenter);
    smtpPassword_->setEchoMode(QLineEdit::Password);
    smtpPassword_->setFixedSize(250, 25);
    smtpPassword_->setText(settings_->value("SMTP/password").toString());

    leftLayout->addRow("ПАРОЛЬ", smtpPassword_);

    //---

    recipientName_ = new QLineEdit(this);
    recipientName_->setStyleSheet("font-size:10pt");
    recipientName_->setAlignment(Qt::AlignCenter);
    recipientName_->setFixedSize(250, 25);
    recipientName_->setText(settings_->value("SMTP/recipient").toString());

    leftLayout->addRow("ПОЛУЧАТЕЛЬ", recipientName_);

    //---

    sendTestMessageLabel_ = new QLabel(this);
    sendTestMessageLabel_->setText("Нажмите, чтобы отправить\nтестовое сообщение");
    sendTestMessageLabel_->setStyleSheet("font-size:8pt; font:italic; color:#ffc000");

    sendTestMessageButton_ = new QPushButton(this);
    sendTestMessageButton_->setFixedSize(100, 24);
    sendTestMessageButton_->setText("ТЕСТ");

    QHBoxLayout* sendTestMessageLayout = new QHBoxLayout;
    sendTestMessageLayout->addStretch();
    sendTestMessageLayout->addWidget(sendTestMessageLabel_);
    sendTestMessageLayout->addWidget(sendTestMessageButton_);
    leftLayout->addRow(sendTestMessageLayout);

    //---

    connect(avaliableSerialPorts_, SIGNAL(currentTextChanged(const QString&)), this, SIGNAL(serialPortChanged(const QString&)));

    //---

    connect(sendTestMessageButton_, SIGNAL(clicked()), this, SLOT(sendTestMessage()));

    //---


}

FunctionsFrame::FunctionsFrame::~FunctionsFrame()
{
    settings_->setValue("functionsFrame/serialPort", avaliableSerialPorts_->currentText());
    settings_->setValue("functionsFrame/flags", mcuInData_->functionsFlags);

    settings_->setValue("SMTP/server", serverName_->text());
    settings_->setValue("SMTP/port", portName_->text());
    settings_->setValue("SMTP/user", userName_->text());
    settings_->setValue("SMTP/password", smtpPassword_->text()); //--- Пока в незашифрованном виде!
    settings_->setValue("SMTP/recipient", recipientName_->text());
    settings_->setValue("SMTP/ssl", sslButton_->isChecked());
    settings_->sync();

    delete smtp_;
}

void FunctionsFrame::refresh()
{

}

void FunctionsFrame::setControlsEnabled(bool state)
{
    // Левая панель

    avaliableSerialPorts_->setEnabled(state);

    startOnBootButton_->setEnabled(state);
    lockOSButton_->setEnabled(state);
    lockAppButton_->setEnabled(state);
    turnOnButton_->setEnabled(state);

    // Правая панель

    serverName_->setEnabled(state);
    portName_->setEnabled(state);
    sslButton_->setEnabled(state);
    userName_->setEnabled(state);
    smtpPassword_->setEnabled(state);
    recipientName_->setEnabled(state);
    sendTestMessageButton_->setEnabled(state);
}



void FunctionsFrame::sendTestMessage()
{
//    qDebug() << "Отправка тестовго сообщения";

    if(!smtp_)
    {
        smtp_ = new SmtpClient(serverName_->text(), portName_->text().toInt());
    }
    else
    {
        smtp_->setHost(serverName_->text());
        smtp_->setPort(portName_->text().toInt());
    }

    if(sslButton_->isChecked()) smtp_->setConnectionType(SmtpClient::SslConnection);
    else smtp_->setConnectionType(SmtpClient::TcpConnection);
    smtp_->setUser(userName_->text());
    smtp_->setPassword(smtpPassword_->text());
    MimeMessage message;
    message.setSender(new EmailAddress(userName_->text(), ""));
    message.addRecipient(new EmailAddress(recipientName_->text(), "Recipient's Name"));
    message.setSubject("Тестовое сообщение KRAKENONE");
    MimeText text;
    text.setText("Hi,\nThis is a simple email message.\n");
    message.addPart(&text);
    smtp_->connectToHost();
    smtp_->login();
    smtp_->sendMail(message);
    smtp_->quit();
}
