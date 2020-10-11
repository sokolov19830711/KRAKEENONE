#ifndef FUNCTIONSFRAME_H
#define FUNCTIONSFRAME_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>

#include "onoffbutton.h"
#include "frame.h"
#include "../SmtpClient-for-Qt/src/SmtpMime"

class FunctionsFrame : public Frame
{
    Q_OBJECT
public:
    FunctionsFrame(QSharedPointer<QSettings> settings, McuInData* mcuInData, McuOutData* mcuOutData, const QString& serialPortName, QWidget *parent = nullptr);
    virtual ~FunctionsFrame();

    virtual void refresh();
    virtual void setControlsEnabled(bool state = true);

signals:

    void serialPortChanged(const QString& portName);

public slots:

    void sendTestMessage();

private:

    // Левая панель

    QComboBox* avaliableSerialPorts_;

	OnOffButton* startOnBootButton_;
    OnOffButton* lockOSButton_;
    OnOffButton* lockAppButton_;
    OnOffButton* turnOnButton_;

    // Правая панель
    QLabel* notificationLabel_;

    QLabel* serverNameExampleLabel_;
    QLineEdit* serverName_;

    QLabel* portLabel_;
    QLabel* portExampleLabel_;
    QLineEdit* portName_;

    QLabel* sslLabel_;
    OnOffButton* sslButton_;

    QLineEdit* userName_;

    QLineEdit* smtpPassword_;

    QLineEdit* senderName_;

    QLabel* sendTestMessageLabel_;
    QPushButton* sendTestMessageButton_;
    SmtpClient* smtp_ = nullptr;

};

#endif // FUNCTIONSFRAME_H
