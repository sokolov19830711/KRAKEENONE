#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QtSerialPort>
#include <QTimer>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QMenu>

#include "firmware/dataStructures.h"
#include "PrimeboxWidgets/SwitchButtonsWidget.h"
#include "serialportmanager.h"
#include "SMTPmessageManager.h"
#include "mainframe.h"
#include "functionsframe.h"
#include "aboutframe.h"
#include "vibrationframe.h"
#include "positionframe.h"
#include "dustframe.h"
#include "moistureframe.h"
#include "temperatureframe.h"
#include "powerframe.h"
#include "breakinframe.h"
#include "runninghoursframe.h"
#include "ibuttonframe.h"
#include "enterpasswordframe.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:

    enum AccessLevel { user, admin };

    explicit MainWidget(QWidget *parent = nullptr);
    virtual ~MainWidget();

signals:

public slots:

    void setDeviceConnected(bool state = true);
    void changeFrame(int index);
    void showMainWidget();
    void logon(const QString& password);
    void refresh();
    void onConnectionLost();
    void sendTestSMTPmessage();
    void showTrayNotification(const QString& text);

protected:

    void closeEvent(QCloseEvent * event);

private slots:

    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);

private:


    bool _isDeviceConnected = false;
    McuInData mcuInData_;
    McuOutData mcuOutData_;

    SwitchButtonsWidget* frameSelectButtons_;

    QStackedWidget* frames_;

    MainFrame* mainFrame_;
    FunctionsFrame* functionsFrame_;
    AboutFrame* aboutFrame_;
    VibrationFrame* vibrationFrame_;
    PositionFrame* positionFrame_;
    DustFrame* dustFrame_;
    MoistureFrame* moistureFrame_;
    TemperatureFrame* temperatureFrame_;
    BreakInFrame* breakInFrame_;
    PowerFrame* powerFrame_;
    RunningHoursFrame* runningHoursFrame_;
    IButtonFrame* iButtonFrame_;

    EnterPasswordFrame* passwordWidget_ = nullptr;

    QTimer* mainTimer_;
    QTimer* messageTimer_;
    QThread* portManagerThread_;
    SerialPortManager* portManager_ = nullptr;

    QSharedPointer<QSettings> settings_;
    SMTPmessageManager* _SMTPmanager;

    QSystemTrayIcon* _trayIcon;
    QMenu* _trayMenu;
    bool _isClosedViaTray = false;
};

#endif // MAINWIDGET_H
