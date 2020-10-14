#include "mainwidget.h"
#include "firmware/dataStructures.h"

#include <QSerialPortInfo>
#include <QDebug>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    settings_ = QSharedPointer<QSettings>::create("settings.ini", QSettings::IniFormat);
    mcuInData_.functionsFlags = settings_->value("functionsFrame/flags").toUInt();

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

    //---

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setMargin(0);

    //--- Создаем группу кнопок, с помощью которых переключаем кадры приложения

    QString buttonsStyle =  "QPushButton:checked{height : 125; width : 125; font : bold; color: #ffffff; border-style:solid; border-width:0.5px; border-color:#7f7f7f; background-color:#c05046;}"
                            "QPushButton{height : 125; width : 125; color: #ffffff; border-style:solid; border-width:0.5px; border-color:#7f7f7f; background-color:#595959;}";

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

    //--- Нижняя панель переключения между пользователем и администратором

    QHBoxLayout* userSwitchLayout = new QHBoxLayout;
    framesLayout->addLayout(userSwitchLayout);

    userSwitchLayout->addStretch();
    QLabel* userSwitchLabel = new QLabel("ПОЛЬЗОВАТЕЛЬ");
    userSwitchLabel->setStyleSheet("color: #ffffff");
    userSwitchLayout->addWidget(userSwitchLabel);

    userSwitchButtons_ = new ButtonGroup({ "ОБЫЧНЫЙ", "АДМИНИСТРАТОР" }, 100, 25, this);
    userSwitchButtons_->setChecked(1); // По умолчанию запускаемся под обычным пользователем
    userSwitchLayout->addWidget(userSwitchButtons_);

    connect(userSwitchButtons_, &ButtonGroup::idClicked, this, &MainWidget::changeUser);

    //--- Таймер

    mainTimer_ = new QTimer(this);
    connect(mainTimer_, SIGNAL(timeout()), this, SLOT(refresh()));
    mainTimer_->start(100);
}

MainWidget::~MainWidget()
{
    portManagerThread_->quit();
    delete  portManager_;
}

void MainWidget::changeFrame(int index)
{
    frames_->setCurrentIndex(index);
    Frame* currentFrame = dynamic_cast<Frame*> (frames_->widget(index));

    if(currentFrame)
    {
        switch (userAccessLevel_)
        {
        default:
        case user:
            currentFrame->setControlsEnabled(false);
            break;

        case admin:
            currentFrame->setControlsEnabled();
            break;
        }
    }
}

void MainWidget::changeUser(int level)
{
    switch (level)
    {
    default:
    case user:
        userAccessLevel_ = user;
        (dynamic_cast<Frame*> (frames_->currentWidget()))->setControlsEnabled(false);
        break;

    case admin:

        userSwitchButtons_->setChecked(user);
        passwordWidget_ = new EnterPasswordFrame();
        passwordWidget_->setWindowModality(Qt::ApplicationModal);
        passwordWidget_->show();
        connect(passwordWidget_, &EnterPasswordFrame::passwordAttempted, this, &MainWidget::logon);
        break;
    }
}

void MainWidget::logon(const QString& password)
{
    if (
        (password.isEmpty() && settings_->value("password") == QVariant()) || // Пароль не установлен
        ((settings_->value("password")).toByteArray() == QCryptographicHash::hash(QString(password + "q[fdfj").toUtf8(), QCryptographicHash::Algorithm::Md5))
        )
    {
        userAccessLevel_ = admin;
        userSwitchButtons_->setChecked(admin);
        (dynamic_cast<Frame*> (frames_->currentWidget()))->setControlsEnabled(true);
        delete passwordWidget_;
    }

    else 
    {
        userAccessLevel_ = user;
        userSwitchButtons_->setChecked(user);
        (dynamic_cast<Frame*> (frames_->currentWidget()))->setControlsEnabled(false);
    }
}

void MainWidget::refresh()
{
    (dynamic_cast<Frame*>(frames_->currentWidget()))->refresh();
}

void MainWidget::closeEvent(QCloseEvent *event)
{
    settings_->sync();

    QWidget::closeEvent(event);
}

