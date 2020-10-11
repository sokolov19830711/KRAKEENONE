#ifndef ABOUTFRAME_H
#define ABOUTFRAME_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPlainTextEdit>

#include "frame.h"

class AboutFrame : public Frame
{
    Q_OBJECT

public:

    AboutFrame(QSharedPointer<QSettings> settings, McuInData* mcuInData, McuOutData* mcuOutData, QWidget *parent = nullptr);

	virtual void setControlsEnabled(bool state = true);

signals:

public slots:

private:

	QLabel* enterActivationKeyLabel_;
	QLineEdit* activationKey_;
	QPushButton* activateButton_;

    QPlainTextEdit* infoText_;
};

#endif // ABOUTFRAME_H
