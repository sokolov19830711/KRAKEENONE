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

#include "firmware/dataStructures.h"
#include "serialportmanager.h"
#include "PrimeboxWidgets/SwitchButtonsWidget.h"
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

    enum AccessLevel { user = 1, admin };

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

private:

    AccessLevel userAccessLevel_ = user;

    McuInData mcuInData_;
    McuOutData mcuOutData_;

    SwitchButtonsWidget* frameSelectButtons_;

    QPushButton* mainButton_;
    QPushButton* functionsButton_;
    QPushButton* aboutButton_;
    QPushButton* vibrationButton_;
    QPushButton* positionButton_;
    QPushButton* dustButton_;
    QPushButton* moistureButton_;
    QPushButton* temperatureButton_;
    QPushButton* powerButton_;
    QPushButton* breakInButton_;
    QPushButton* runningHoursButton_;
    QPushButton* IButtonButton_;

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

    ButtonGroup* userSwitchButtons_;

    QTimer* mainTimer_;
    QThread* portManagerThread_;
    SerialPortManager* portManager_ = nullptr;

    QSharedPointer<QSettings> settings_;
};

#endif // MAINWIDGET_H
