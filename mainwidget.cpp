#include "mainwidget.h"
#include "firmware/dataStructures.h"

#ifdef Q_OS_WIN32
#include <windows.h>
#endif

#include <QSerialPortInfo>
#include <QDebug>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    appStartedTime_ = QDateTime::currentDateTime();

    setStyleSheet("background-color:#205867");

    settings_ = QSharedPointer<QSettings>::create(QCoreApplication::applicationDirPath() + "/settings.ini", QSettings::IniFormat);

    _SMTPmanager = new SMTPmessageManager(settings_);
    connect(_SMTPmanager, SIGNAL(needToShowEvent(const QString&)), this, SLOT(showTrayNotification(const QString&)));

    mcuInData_.functionsFlags = settings_->value("functionsFrame/flags").toUInt();

    mcuInData_.vibrationFlags1 = settings_->value("vibrationFrame/flags1").toUInt();
    mcuInData_.vibrationFlags2 = settings_->value("vibrationFrame/flags2").toUInt();
    mcuInData_.vibrationFlags3 = settings_->value("vibrationFrame/flags3").toUInt();
    mcuInData_.vibrationFlags4 = settings_->value("vibrationFrame/flags4").toUInt();

    mcuInData_.vibrationMaxValue1 = settings_->value("vibrationFrame/maxValue1").toInt();
    mcuInData_.vibrationMaxValue2 = settings_->value("vibrationFrame/maxValue2").toInt();
    mcuInData_.vibrationMaxValue3 = settings_->value("vibrationFrame/maxValue3").toInt();
    mcuInData_.vibrationMaxValue4 = settings_->value("vibrationFrame/maxValue4").toInt();

    mcuInData_.positionFlags = settings_->value("positionFrame/flags").toUInt();
    mcuInData_.positionXnormal = settings_->value("positionFrame/positionXnormal").toInt();
    mcuInData_.positionYnormal = settings_->value("positionFrame/positionYnormal").toInt();
    mcuInData_.positionZnormal = settings_->value("positionFrame/positionZnormal").toInt();
	mcuInData_.positionXdeviation = settings_->value("positionFrame/positionXdeviation").toInt();
	mcuInData_.positionYdeviation = settings_->value("positionFrame/positionYdeviation").toInt();
	mcuInData_.positionZdeviation = settings_->value("positionFrame/positionZdeviation").toInt();

    mcuInData_.dustFlags1 = settings_->value("dustFrame/flags1").toUInt();
    mcuInData_.dustFlags2 = settings_->value("dustFrame/flags2").toUInt();
    mcuInData_.dustFlags3 = settings_->value("dustFrame/flags3").toUInt();

    mcuInData_.dustMaxValue1 = settings_->value("dustFrame/maxValue1").toInt();
    mcuInData_.dustMaxValue2 = settings_->value("dustFrame/maxValue2").toInt();
    mcuInData_.dustMaxValue3 = settings_->value("dustFrame/maxValue3").toInt();

    mcuInData_.moistureFlags = settings_->value("moistureFrame/flags").toUInt();
    mcuInData_.moistureMinValue = settings_->value("moistureFrame/minValue").toInt();
    mcuInData_.moistureMaxValue = settings_->value("moistureFrame/maxValue").toInt();

    mcuInData_.temperatureFlags1 = settings_->value("temperatureFrame/flags1").toUInt();
    mcuInData_.temperatureFlags2 = settings_->value("temperatureFrame/flags2").toUInt();
    mcuInData_.temperatureFlags3 = settings_->value("temperatureFrame/flags3").toUInt();

    mcuInData_.temperatureMinValue1 = settings_->value("temperatureFrame/minValue1").toInt();
    mcuInData_.temperatureMinValue2 = settings_->value("temperatureFrame/minValue2").toInt();
    mcuInData_.temperatureMinValue3 = settings_->value("temperatureFrame/minValue3").toInt();

    mcuInData_.temperatureMaxValue1 = settings_->value("temperatureFrame/maxValue1").toInt();
    mcuInData_.temperatureMaxValue2 = settings_->value("temperatureFrame/maxValue2").toInt();
    mcuInData_.temperatureMaxValue3 = settings_->value("temperatureFrame/maxValue3").toInt();

    mcuInData_.breakInFlags1 = settings_->value("breakInFrame/flags1").toUInt();
    mcuInData_.breakInFlags2 = settings_->value("breakInFrame/flags2").toUInt();
    mcuInData_.breakInFlags3 = settings_->value("breakInFrame/flags3").toUInt();

    mcuInData_.breakInSensorNormalState1 = settings_->value("breakInFrame/sensorState1").toInt();
    mcuInData_.breakInSensorNormalState2 = settings_->value("breakInFrame/sensorState2").toInt();
    mcuInData_.breakInSensorNormalState3 = settings_->value("breakInFrame/sensorState3").toInt();

    mcuInData_.powerButtonPwdLevel = settings_->value("PWR/powerButtonPwdLevel").toInt();
    mcuInData_.powerButtonPwdDigit1 = settings_->value("PWR/digit1").toInt();
    mcuInData_.powerButtonPwdDigit2 = settings_->value("PWR/digit2").toInt();
    mcuInData_.powerButtonPwdDigit3 = settings_->value("PWR/digit3").toInt();
    mcuInData_.digitInputPeriod = settings_->value("PWR/digitInputPeriod", 3).toInt();

    mcuInData_.iButtonFlags = settings_->value("iButtonFrame/flags").toUInt();
    mcuInData_.wrongKeyUsageForPowerOff = settings_->value("iButtonFrame/wrongKeyUsageForPowerOff").toInt();
    mcuInData_.wrongKeyUsageForReset = settings_->value("iButtonFrame/wrongKeyUsageForReset").toInt();

    mcuInData_.isPWRavaliable = settings_->value("PWR/isPWRavaliable").toBool() ? 1 : 0;
    mcuInData_.isRSTavaliable = settings_->value("PWR/isRSTavaliable").toBool() ? 1 : 0;

    // Настраиваем COM-порт, к которому подключен контроллер

    auto ports = QSerialPortInfo::availablePorts();
    qDebug() << "Avaliable COM-ports:";
    for(auto & i : ports)
    {
        qDebug() << i.description() << " on " << i.portName();
    }

    if(ports.size())
    {
        for(auto & i : ports)
        {
            if (i.portName() == settings_->value("functionsFrame/serialPort").toString())
            {
                portManagerThread_ = new QThread(this);
                portManager_ = new SerialPortManager(i, &mcuInData_, &mcuOutData_);

                portManager_->moveToThread(portManagerThread_);
                portManagerThread_->start();
                break;
            }
        }

        if (!portManager_) //--- Тут нужно обработать ситуацию, когда сохраненный в настройках порт не доступен
        {
            portManagerThread_ = new QThread(this);
            portManager_ = new SerialPortManager(ports.first(), &mcuInData_, &mcuOutData_);

            portManager_->moveToThread(portManagerThread_);
            portManagerThread_->start();
        }
    }

    else //--- Вообще нет доступных портов
    {
        portManagerThread_ = new QThread(this);
        portManager_ = new SerialPortManager();

        portManager_->moveToThread(portManagerThread_);
        portManagerThread_->start();
    }

    connect(portManager_, SIGNAL(noConnection()), this, SLOT(onConnectionLost()));
    connect(portManager_, SIGNAL(deviceConnected(bool)), this, SLOT(setDeviceConnected(bool)));

    //---

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setMargin(0);

    //--- Создаем группу кнопок, с помощью которых переключаем кадры приложения

    QString buttonsStyle =  "QPushButton:checked{height : 131; width : 131; font : bold; color: #ffffff; border-style:solid; border-width:0.5px; border-color:#7f7f7f; background-color:#c05046;}"
                            "QPushButton{height : 131; width : 131; color: #ffffff; border-style:solid; border-width:0.5px; border-color:#7f7f7f; background-color:#595959;}";

    QStringList buttonTextes = { "ГЛАВНАЯ\n\n(главная страница,\nмониторинг)", "ФУНКЦИИ\n\n(настройка\nвыполняемых\nфункций)", "О ПРОГРАММЕ\n\n(подробнее об\nустройстве,\nконтакты)",
                                 "ВИБРАЦИЯ | УДАР\n\n(настройка датчика\nвибрации и удара)",  "ПОЛОЖЕНИЕ\n\n(настройка датчика\nположения,\nперемещения)", "ЗАПЫЛЕННОСТЬ\n\n(настройка датчика\nзапыленности,\nкорпуса)",
                                 "ВЛАЖНОСТЬ\n\n(настройка датчика\nвлажности)",  "ТЕМПЕРАТУРА\n\n(настройка датчиков\nтемпературы)", "POWER | RST\n\n(настройка функций\nкнопок питания и\nперезагрузки)",
                                 "ВСКРЫТИЕ\n\n(настройка\nповедения датчика\nвскрытия)", "НАРАБОТКА | АКБ\n\n(индикация\nвремени нарабтки\nкомпьютера)", "IBUTTON\n\n(настройка\nавторизации\nбесконтактным\nключем)" };

    frameSelectButtons_ = new SwitchButtonsWidget(4, 3, buttonsStyle, buttonTextes, this);
    mainLayout->addWidget(frameSelectButtons_);
    frameSelectButtons_->setChecked(0);

    QVBoxLayout* framesLayout = new QVBoxLayout;
    mainLayout->addLayout(framesLayout);

    //--- Заголовок, отображаемый над всеми кадрами

    QLabel* workAreaTitle1 = new QLabel(this);
    workAreaTitle1->setStyleSheet("color: #ffffff;");
    workAreaTitle1->setText("by.TRUEDEVICE");

    QLabel* workAreaTitle2 = new QLabel(this);
    workAreaTitle2->setStyleSheet("font-size : 16pt; color: #ffffff;");
    workAreaTitle2->setText("PRIMEBOX");

    QLabel* workAreaTitle3 = new QLabel(this);
    workAreaTitle3->setStyleSheet("color: #ffffff;");
    workAreaTitle3->setText("KRAKEEN.one");

    QHBoxLayout* titleLayout = new QHBoxLayout;
    titleLayout->addStretch();
    titleLayout->addWidget(workAreaTitle1);
    titleLayout->addWidget(workAreaTitle2);
    titleLayout->addWidget(workAreaTitle3);
    titleLayout->addStretch();
    framesLayout->addSpacing(12);
    framesLayout->addLayout(titleLayout);

    //--- Создаем набор кадров приложения

    frames_ = new QStackedWidget(this);
    framesLayout->addWidget(frames_);

    mainFrame_ = new MainFrame(settings_, &mcuInData_, &mcuOutData_);
    frames_->addWidget(mainFrame_);

    functionsFrame_ = new FunctionsFrame(settings_, &mcuInData_, &mcuOutData_, portManager_->getPortName());
    frames_->addWidget(functionsFrame_);
    connect(functionsFrame_, SIGNAL(testMessageButtonClicked()), this, SLOT(sendTestSMTPmessage()));

    aboutFrame_ = new AboutFrame(settings_, &mcuInData_, &mcuOutData_);
    frames_->addWidget(aboutFrame_);

    vibrationFrame_ = new VibrationFrame(settings_, &mcuInData_, &mcuOutData_);
    frames_->addWidget(vibrationFrame_);

    positionFrame_ = new PositionFrame(settings_, &mcuInData_, &mcuOutData_);
    frames_->addWidget(positionFrame_);

    dustFrame_ = new DustFrame(settings_, &mcuInData_, &mcuOutData_);
    frames_->addWidget(dustFrame_);

    moistureFrame_ = new MoistureFrame(settings_, &mcuInData_, &mcuOutData_);
    frames_->addWidget(moistureFrame_);

    temperatureFrame_ = new TemperatureFrame(settings_, &mcuInData_, &mcuOutData_);
    frames_->addWidget(temperatureFrame_);

    powerFrame_ = new PowerFrame(settings_, &mcuInData_, &mcuOutData_);
    frames_->addWidget(powerFrame_);

    breakInFrame_ = new BreakInFrame(settings_, &mcuInData_, &mcuOutData_);
    frames_->addWidget(breakInFrame_);

    runningHoursFrame_ = new RunningHoursFrame(settings_, &mcuInData_, &mcuOutData_);
    frames_->addWidget(runningHoursFrame_);

    iButtonFrame_ = new IButtonFrame(settings_, &mcuInData_, &mcuOutData_);
    frames_->addWidget(iButtonFrame_);

    changeFrame(0);

    //---

    connect(frameSelectButtons_, SIGNAL(idClicked(int)), this, SLOT(changeFrame(int)));

    //---

    connect(functionsFrame_, SIGNAL(serialPortChanged(const QString&)), portManager_, SLOT(setPort(const QString&)));


    //--- Таймеры

    mainTimer_ = new QTimer(this);
    connect(mainTimer_, SIGNAL(timeout()), this, SLOT(refresh()));
    mainTimer_->start(100);

    messageTimer_ = new QTimer(this);
    connect(messageTimer_, SIGNAL(timeout()), _SMTPmanager, SLOT(sendEventLog()));
    messageTimer_->start(300000);

    PC_totalRunningTimeUpdateTimer_ = new QTimer(this);
    connect(PC_totalRunningTimeUpdateTimer_, SIGNAL(timeout()), this, SLOT(updatePcTotalRunningTime()));
    PC_totalRunningTimeUpdateTimer_->start(60000);

    connectionLostMessageTimer_ = new QTimer(this);
    connectionLostMessageTimer_->setSingleShot(true);

    //--- Иконка в трее

	_trayIcon = new QSystemTrayIcon(QIcon(":trayIcon.png"), this);
    _trayIcon->setToolTip("Программа мониторинга\nKRAKEENONE");
    _trayIcon->show();

    _trayMenu = new QMenu;
	QAction* viewWindow = new QAction("Открыть окно", this);
	QAction* quitAction = new QAction("Выход", this);
    _trayMenu->addAction(viewWindow);
    _trayMenu->addAction(quitAction);

    connect(viewWindow, SIGNAL(triggered()), this, SLOT(showMainWidget()));

    connect(quitAction, &QAction::triggered, [=]()
        {
            _isClosedViaTray = true;
            this->close();
        });

	connect(_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));

    _trayIcon->setContextMenu(_trayMenu);

    //---

	passwordWidget_ = new EnterPasswordFrame();
	connect(passwordWidget_, &EnterPasswordFrame::passwordAttempted, this, &MainWidget::logon);

    //---

	updatePcTotalRunningTime();
}

MainWidget::~MainWidget()
{
    portManagerThread_->quit();
    delete  portManager_;
    delete _trayMenu;
    delete passwordWidget_;
    delete _SMTPmanager;
}

void MainWidget::setDeviceConnected(bool state)
{
    _isDeviceConnected = state;
}

void MainWidget::changeFrame(int index)
{
    frames_->setCurrentIndex(index);
}

void MainWidget::showMainWidget()
{
	passwordWidget_->show();
}

void MainWidget::logon(const QString& password)
{
    if (
        (password.isEmpty() && settings_->value("password") == QVariant()) || // Пароль не установлен
        ((settings_->value("password")).toByteArray() == QCryptographicHash::hash(QString(password + "q[fdfj").toUtf8(), QCryptographicHash::Algorithm::Md5))
        )
    {
        this->show();
        passwordWidget_->hide();
    }
}

void MainWidget::refresh()
{
    // Обновляем GUI видимого кадра
    (dynamic_cast<Frame*>(frames_->currentWidget()))->refresh(_isDeviceConnected);

    if (!_isDeviceConnected)
    {
        return;
    }

    // Обрабатываем данные с датчиков -------------------------------------------------

    // Датчики вскрытия
    if (mcuOutData_.breakInSensor1 != mcuInData_.breakInSensorNormalState1)
    {
        QString logMessage = "Срабатывание датчика вскрытия №1";
		if (mcuInData_.breakInFlags1 & ActionsFlag::notification)
		{
			_SMTPmanager->addEventToLog(logMessage);
		}
    }
	
	if (mcuOutData_.breakInSensor2 != mcuInData_.breakInSensorNormalState2)
	{
		QString logMessage = "Срабатывание датчика вскрытия №2";
		if (mcuInData_.breakInFlags2 & ActionsFlag::notification)
		{
			_SMTPmanager->addEventToLog(logMessage);
		}
	}

	if (mcuOutData_.breakInSensor3 != mcuInData_.breakInSensorNormalState3)
	{
		QString logMessage = "Срабатывание датчика вскрытия №3";
		if (mcuInData_.breakInFlags3 & ActionsFlag::notification)
		{
			_SMTPmanager->addEventToLog(logMessage);
		}
	}
	

    // Датчики температуры
    if ((mcuOutData_.temperatureSensor1 > mcuInData_.temperatureMaxValue1) ||
        (mcuOutData_.temperatureSensor1 < mcuInData_.temperatureMinValue1))
    {
        if (mcuInData_.temperatureFlags1 & ActionsFlag::notification)
        {
            _SMTPmanager->addEventToLog(QString("Срабатывание датчика температуры №1. Значение: %1").arg(mcuOutData_.temperatureSensor1));
        }
    }

	if ((mcuOutData_.temperatureSensor2 > mcuInData_.temperatureMaxValue2) ||
		(mcuOutData_.temperatureSensor2 < mcuInData_.temperatureMinValue2))
	{
		if (mcuInData_.temperatureFlags2 & ActionsFlag::notification)
		{
			_SMTPmanager->addEventToLog(QString("Срабатывание датчика температуры №2. Значение: %1").arg(mcuOutData_.temperatureSensor2));
		}
	}

	if ((mcuOutData_.temperatureSensor3 > mcuInData_.temperatureMaxValue3) ||
		(mcuOutData_.temperatureSensor3 < mcuInData_.temperatureMinValue3))
	{
		if (mcuInData_.temperatureFlags3 & ActionsFlag::notification)
		{
			_SMTPmanager->addEventToLog(QString("Срабатывание датчика температуры №3. Значение: %1").arg(mcuOutData_.temperatureSensor3));
		}
	}

	// Датчик влажности
    if (mcuOutData_.moistureSensor > mcuInData_.moistureMaxValue)
    {
		if (mcuInData_.moistureFlags & ActionsFlag::notification)
		{
			_SMTPmanager->addEventToLog(QString("Срабатывание датчика влажности. Значение: %1").arg(mcuOutData_.moistureSensor));
		}
    }

	// Датчики запыленности
    if (mcuOutData_.dustSensor1 > mcuInData_.dustMaxValue1)
    {
		if (mcuInData_.dustFlags1 & ActionsFlag::notification)
		{
			_SMTPmanager->addEventToLog(QString("Срабатывание датчика запыленности №1. Значение: %1").arg(mcuOutData_.dustSensor1));
		}
    }

	if (mcuOutData_.dustSensor2 > mcuInData_.dustMaxValue2)
	{
		if (mcuInData_.dustFlags2 & ActionsFlag::notification)
		{
			_SMTPmanager->addEventToLog(QString("Срабатывание датчика запыленности №2. Значение: %1").arg(mcuOutData_.dustSensor2));
		}
	}

	if (mcuOutData_.dustSensor3 > mcuInData_.dustMaxValue3)
	{
		if (mcuInData_.dustFlags3 & ActionsFlag::notification)
		{
			_SMTPmanager->addEventToLog(QString("Срабатывание датчика запыленности №3. Значение: %1").arg(mcuOutData_.dustSensor3));
		}
	}

	// Датчики вибрации
    if (mcuOutData_.vibrationSensor1 > mcuInData_.vibrationMaxValue1)
    {
        if (mcuInData_.vibrationFlags1 & ActionsFlag::notification)
        {
            _SMTPmanager->addEventToLog(QString("Срабатывание встроенного датчика вибрации. Значение: %1").arg(mcuOutData_.vibrationSensor1));
        }
    }

	if (mcuOutData_.vibrationSensor2 > mcuInData_.vibrationMaxValue2)
	{
		if (mcuInData_.vibrationFlags2 & ActionsFlag::notification)
		{
			_SMTPmanager->addEventToLog(QString("Срабатывание датчика вибрации №2. Значение: %1").arg(mcuOutData_.vibrationSensor2));
		}
	}

	if (mcuOutData_.vibrationSensor3 > mcuInData_.vibrationMaxValue3)
	{
		if (mcuInData_.vibrationFlags3 & ActionsFlag::notification)
		{
			_SMTPmanager->addEventToLog(QString("Срабатывание датчика вибрации №3. Значение: %1").arg(mcuOutData_.vibrationSensor3));
		}
	}

	if (mcuOutData_.vibrationSensor4 > mcuInData_.vibrationMaxValue4)
	{
		if (mcuInData_.vibrationFlags4 & ActionsFlag::notification)
		{
			_SMTPmanager->addEventToLog(QString("Срабатывание датчика вибрации №4. Значение: %1").arg(mcuOutData_.vibrationSensor4));
		}
	}
}

void MainWidget::onConnectionLost()
{
    _isDeviceConnected = false;
    if (!connectionLostMessageTimer_->isActive())
    {
        showTrayNotification("Потеряна связь с управляющим устройством, или устройство отключено!");
        connectionLostMessageTimer_->start(120000);
    }
    if (mcuInData_.functionsFlags & FunctionsFlag::lockOS)
    {
#ifdef Q_OS_WIN32
        LockWorkStation();
#endif
    }
}

void MainWidget::sendTestSMTPmessage()
{
    _SMTPmanager->sendMessage({ "Тестовое сообщение от KRAKEENONE" });
}

void MainWidget::closeEvent(QCloseEvent *event)
{
    settings_->sync();

    if (_isClosedViaTray)
    {
        QWidget::closeEvent(event);
    }

    else
	{
		event->ignore();
		this->hide();
	}
}

void MainWidget::updatePcTotalRunningTime()
{
    static unsigned prevSessionTotalRunningTime(settings_->value("OS_totalRunningTime").toUInt());
    unsigned elapsedTime = static_cast<unsigned>(appStartedTime_.secsTo(QDateTime::currentDateTime()));
    settings_->setValue("OS_totalRunningTime", prevSessionTotalRunningTime + elapsedTime);
}

void MainWidget::showTrayNotification(const QString& text)
{
	QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::MessageIcon(QSystemTrayIcon::Information);

	_trayIcon->showMessage("KRAKEENONE", text, icon, 2000);
}

void MainWidget::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Unknown:
        break;
    case QSystemTrayIcon::Context:
        break;
    case QSystemTrayIcon::DoubleClick:
        this->showMainWidget();
        break;
    case QSystemTrayIcon::Trigger:
        this->showMainWidget();
        break;
    case QSystemTrayIcon::MiddleClick:
        break;
    default:
        break;
    }
}

