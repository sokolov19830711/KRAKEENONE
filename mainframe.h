#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QWidget>
#include <QLabel>
#include "frame.h"
#include "PrimeboxWidgets/OnOffButton.h"

class MainFrame : public Frame
{
    Q_OBJECT
public:
    MainFrame(QSharedPointer<QSettings> settings, McuInData* mcuInData, McuOutData* mcuOutData, QWidget *parent = nullptr);
    virtual void refresh(bool isDeviceConnected);

signals:

public slots:

private:

    OnOffButton* powerStatusButton_;

    OnOffButton* activityStatusButton_;

    QLabel* ledIndicatorLabel_;
    OnOffButton* ledIndicatorButton1_;
    OnOffButton* ledIndicatorButton2_;

    QLabel* vibrationLabel_;
    OnOffButton* vibrationButton1_;
    OnOffButton* vibrationButton2_;
    OnOffButton* vibrationButton3_;
    OnOffButton* vibrationButton4_;

    OnOffButton* positionButton_;

    QLabel* dustLabel_;
    OnOffButton* dustButton1_;
    OnOffButton* dustButton2_;

    QLabel* moistureLabel_;
    OnOffButton* moistureButton_;

    QLabel* temperatureLabel_;
    OnOffButton* temperatureButton1_;
    OnOffButton* temperatureButton2_;
    OnOffButton* temperatureButton3_;

    QLabel* breakInLabel_;
    OnOffButton* breakInButton1_;
    OnOffButton* breakInButton2_;
    OnOffButton* breakInButton3_;
    OnOffButton* breakInButton4_;

    OnOffButton* iButtonButton_;

};

#endif // MAINFRAME_H
