#include "functionsframe.h"

#include <QSerialPortInfo>
#include <QFormLayout>
#include <QAbstractItemView>
#include <QCoreApplication>
#include <QDir>
#include <QMessageBox>

#include <QDebug>

FunctionsFrame::FunctionsFrame(QSharedPointer<QSettings> settings, McuInData *mcuInData, McuOutData *mcuOutData, const QString &serialPortName, QWidget *parent)
    : Frame(settings, mcuInData, mcuOutData, parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout;
    addMainLayout(mainLayout);

    QFormLayout* leftLayout = new QFormLayout;
    mainLayout->addLayout(leftLayout);

    //---

    avaliableSerialPorts_ = new QComboBox(this);
    avaliableSerialPorts_->setStyleSheet("QComboBox {height : 30px; min-width : 50px; border: 0px; font-size : 10pt} QFrame { border: 0px;}");

    auto ports = QSerialPortInfo::availablePorts();
    for(auto & i : ports)
    {
        avaliableSerialPorts_->addItem(i.portName());
    }
    avaliableSerialPorts_->setCurrentText(serialPortName);
    leftLayout->addRow("ПОДКЛЮЧЕНИЕ ЧЕРЕЗ", avaliableSerialPorts_);

    //---

    startOnBootButton_ = new OnOffButton(this);
    startOnBootButton_->setChecked(settings_->value("functionsFrame/startOnBoot").toBool());
    connect(startOnBootButton_, &OnOffButton::toggled, [=]()
        {
            setBit(mcuInData->functionsFlags, FunctionsFlag::startOnBoot, startOnBootButton_->isChecked());

#ifdef Q_OS_WIN32
            QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
            if (startOnBootButton_->isChecked())
            {
				settings.setValue("KRAKEENONE", QDir::toNativeSeparators(QCoreApplication::applicationFilePath()));
				settings.sync();
            }

            else
            {
				settings.remove("KRAKEENONE");
            }
#endif // Q_OS_WIN32

        });
    startOnBootButton_->setChecked(mcuInData->functionsFlags & FunctionsFlag::startOnBoot);
    leftLayout->addRow("АВТОМАТИЧЕСКИЙ ЗАПУСК ПРИ ЗАГРУЗКЕ\nОПЕРАЦИОННОЙ СИСТЕМЫ", startOnBootButton_);

    //---

    lockOSButton_ = new OnOffButton(this);
    connect(lockOSButton_, &OnOffButton::toggled, [=](){setBit(mcuInData->functionsFlags, FunctionsFlag::lockOS, lockOSButton_->isChecked());});
    lockOSButton_->setChecked(mcuInData->functionsFlags & FunctionsFlag::lockOS);
    leftLayout->addRow("БЛОКИРОВАТЬ КОМПЮТЕР ЕСЛИ\nУСТРОЙСТВО ОТКЛЮЧЕНО", lockOSButton_);

    //---

    lockAppButton_ = new OnOffButton(this);
    connect(lockAppButton_, &OnOffButton::toggled, [=](){setBit(mcuInData->functionsFlags, FunctionsFlag::lockApp, lockAppButton_->isChecked());});
    lockAppButton_->setChecked(mcuInData->functionsFlags & FunctionsFlag::lockApp);
    leftLayout->addRow("БЛОКИРОВАТЬ ПРИЛОЖЕНИЕ ПОСЛЕ ТРЕХ\nПОПЫТОК ВВОДА ПАРОЛЯ", lockAppButton_);

    //---

    turnOnButton_ = new OnOffButton(this);
    connect(turnOnButton_, &OnOffButton::toggled, [=](){setBit(mcuInData->functionsFlags, FunctionsFlag::turnOn, turnOnButton_->isChecked());});
    turnOnButton_->setChecked(mcuInData->functionsFlags & FunctionsFlag::turnOn);
    leftLayout->addRow("ВКЛЮЧИТЬ / ВЫКЛЮЧИТЬ УСТРОЙСТВО", turnOnButton_);

    //---

    leftLayout->addRow(new QLabel());

    QVBoxLayout* changePasswordLayout = new QVBoxLayout;
    leftLayout->addRow(changePasswordLayout);

    QHBoxLayout* changePasswordTitleLayout = new QHBoxLayout;
    changePasswordLayout->addLayout(changePasswordTitleLayout);

    changePasswordTitleLayout->addStretch();
    changePasswordTitleLayout->addWidget(new QLabel("ИЗМЕНИТЬ ПАРОЛЬ ПРИЛОЖЕНИЯ"));
    changePasswordTitleLayout->addStretch();

    changePasswordLayout->addSpacing(10);

    QLabel* currentPasswordLabel = new QLabel("ТЕКУЩИЙ ПАРОЛЬ", this);
    currentPasswordLineEdit_ = new QLineEdit(this);
    currentPasswordLineEdit_->setFixedSize(200, 25);
    currentPasswordLineEdit_->setEchoMode(QLineEdit::Password);
    currentPasswordLineEdit_->setAlignment(Qt::AlignCenter);

    QHBoxLayout* currentPasswordLineEditLayout = new QHBoxLayout;
    changePasswordLayout->addLayout(currentPasswordLineEditLayout);
    currentPasswordLineEditLayout->addWidget(currentPasswordLabel);
    currentPasswordLineEditLayout->addWidget(currentPasswordLineEdit_);

	QLabel* newPasswordLabel = new QLabel("НОВЫЙ ПАРОЛЬ", this);
	newPasswordLineEdit_ = new QLineEdit(this);
	newPasswordLineEdit_->setFixedSize(200, 25);
	newPasswordLineEdit_->setEchoMode(QLineEdit::Password);
	newPasswordLineEdit_->setAlignment(Qt::AlignCenter);

	QHBoxLayout* newPasswordLineEditLayout = new QHBoxLayout;
	changePasswordLayout->addLayout(newPasswordLineEditLayout);
	newPasswordLineEditLayout->addWidget(newPasswordLabel);
	newPasswordLineEditLayout->addWidget(newPasswordLineEdit_);

    QHBoxLayout* changePasswordButtonLayout = new QHBoxLayout;
    changePasswordLayout->addLayout(changePasswordButtonLayout);

    changePasswordButton_ = new QPushButton(this);
    changePasswordButton_->setFixedSize(100, 24);
    changePasswordButton_->setText("ИЗМЕНИТЬ");

	if (!(settings_->value("password") == QVariant()))
    {
        changePasswordButton_->setEnabled(false);
    }

    changePasswordButtonLayout->addStretch();
    changePasswordButtonLayout->addWidget(changePasswordButton_);

    connect(currentPasswordLineEdit_, &QLineEdit::textChanged, [=]()
        {
            QString password = currentPasswordLineEdit_->text();
			if (
				(password.isEmpty() && settings_->value("password") == QVariant()) || // Пароль не установлен
				((settings_->value("password")).toByteArray() == QCryptographicHash::hash(QString(password + "q[fdfj").toUtf8(), QCryptographicHash::Algorithm::Md5))
				)
			{
                changePasswordButton_->setEnabled(true);
			}

            else
            {
                changePasswordButton_->setEnabled(false);
            }
        });

    connect(changePasswordButton_, &QPushButton::clicked, [=]()
        {
            if (newPasswordLineEdit_->text() == "")
            {
                settings_->remove("password");
                settings_->sync();
                QMessageBox::information(this, "Изменение пароля приложения", "Пароль для входа в приложение сброшен!");
            }
            else
			{
				settings_->setValue("password", QCryptographicHash::hash(QString(newPasswordLineEdit_->text() + "q[fdfj").toUtf8(), QCryptographicHash::Algorithm::Md5));
				settings_->sync();
				QMessageBox::information(this, "Изменение пароля приложения", "Пароль для входа в приложение успешно изменен!");
			}

            currentPasswordLineEdit_->clear();
            newPasswordLineEdit_->clear();
        });

    //-----------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------

    QFormLayout* rightLayout = new QFormLayout;
    mainLayout->addSpacing(50);
    mainLayout->addLayout(rightLayout);

    notificationLabel_ = new QLabel(this);
    notificationLabel_->setText("НАСТРОЙКА УВЕДОМЛЕНИЙ");
    rightLayout->addRow(notificationLabel_);

    //---

    serverName_ = new QLineEdit(this);
    serverName_->setToolTip("ПРИМЕР: smtp.mail.ru");
    serverName_->setStyleSheet("font-size:10pt");
    serverName_->setAlignment(Qt::AlignCenter);
    serverName_->setFixedSize(250, 25);
    serverName_->setText(settings_->value("SMTP/server").toString());

    rightLayout->addRow("СЕРВЕР", serverName_);

    //---

    portName_ = new QLineEdit(this);
    portName_->setToolTip("ПРИМЕР: 465");
    portName_->setStyleSheet("font-size:10pt");
    portName_->setAlignment(Qt::AlignCenter);
    portName_->setFixedSize(100, 25);
    portName_->setText(settings_->value("SMTP/port").toString());

    sslLabel_ = new QLabel(this);
    sslLabel_->setText("SSL");

    sslButton_ = new OnOffButton(this);
    sslButton_->setChecked(settings_->value("SMTP/ssl").toBool());

    QHBoxLayout* portAndSslLayout = new QHBoxLayout;
    portAndSslLayout->addWidget(portName_);
    portAndSslLayout->addStretch();
    portAndSslLayout->addWidget(sslLabel_);
    portAndSslLayout->addWidget(sslButton_);

    rightLayout->addRow("ПОРТ", portAndSslLayout);

    //---

    userName_ = new QLineEdit(this);
    userName_->setStyleSheet("font-size:10pt");
    userName_->setAlignment(Qt::AlignCenter);
    userName_->setFixedSize(250, 25);
    userName_->setText(settings_->value("SMTP/user").toString());

    rightLayout->addRow("ПОЛЬЗОВАТЕЛЬ", userName_);

    //---

    smtpPassword_ = new QLineEdit(this);
    smtpPassword_->setStyleSheet("font-size:10pt");
    smtpPassword_->setAlignment(Qt::AlignCenter);
    smtpPassword_->setEchoMode(QLineEdit::Password);
    smtpPassword_->setFixedSize(250, 25);
    smtpPassword_->setText(settings_->value("SMTP/password").toString());

    rightLayout->addRow("ПАРОЛЬ", smtpPassword_);

    //---

    recipientName_ = new QLineEdit(this);
    recipientName_->setStyleSheet("font-size:10pt");
    recipientName_->setAlignment(Qt::AlignCenter);
    recipientName_->setFixedSize(250, 25);
    recipientName_->setText(settings_->value("SMTP/recipient").toString());

    rightLayout->addRow("ПОЛУЧАТЕЛЬ", recipientName_);

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
    rightLayout->addRow(sendTestMessageLayout);

    //---

    connect(avaliableSerialPorts_, SIGNAL(currentTextChanged(const QString&)), this, SIGNAL(serialPortChanged(const QString&)));

    //---

    connect(sendTestMessageButton_, SIGNAL(clicked()), this, SIGNAL(testMessageButtonClicked()));

    //---


}

FunctionsFrame::FunctionsFrame::~FunctionsFrame()
{
    settings_->setValue("functionsFrame/serialPort", avaliableSerialPorts_->currentText());
    settings_->setValue("functionsFrame/flags", mcuInData_->functionsFlags);

    settings_->setValue("functionsFrame/startOnBoot", startOnBootButton_->isChecked());

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
