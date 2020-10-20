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

#include "firmware/dataStructures.h"
#include "PrimeboxWidgets/SwitchButtonsWidget.h"
#include "serialportmanager.h"
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

    void changeFrame(int index);
    void changeUser(int level);
    void logon(const QString& password);
    void refresh();

protected:

    void closeEvent(QCloseEvent * event);

private slots:

    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);

private:

    AccessLevel userAccessLevel_ = user;

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

    SwitchButtonsWidget* userSwitchButtons_;

    QTimer* mainTimer_;
    QThread* portManagerThread_;
    SerialPortManager* portManager_ = nullptr;

    QSharedPointer<QSettings> settings_;

    QSystemTrayIcon* _trayIcon;
    bool _isClosedViaTray = false;
};

#endif // MAINWIDGET_H
