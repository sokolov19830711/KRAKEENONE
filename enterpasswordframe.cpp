#include "enterpasswordframe.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "mainwidget.h"

EnterPasswordFrame::EnterPasswordFrame(QWidget* parent) : QWidget(parent)
{
    setFixedSize(300, 450);
    setStyleSheet(
        "QWidget{background-color:#205867}"
        "QLabel{color:#ffffff}"
        "QPushButton{border-style:solid; border-width:1px; border-color:#0070c0; color:#ffffff; background:#0070c0}"
        "QPushButton:pressed{border-style:solid; border-width:1px; border-color:#444444; color:#ffffff; background:#0070c0}"
        "QLineEdit,QComboBox{color:#333333; background:#f0f0f0}"
       );

    QVBoxLayout* mainLayout = new QVBoxLayout;
    setLayout(mainLayout);

    //---

    QHBoxLayout* appNameLayout1 = new QHBoxLayout;
    mainLayout->addLayout(appNameLayout1);
    appNameLayout1->addStretch();
    QLabel* line1 = new QLabel("PRIMEBOX", this);
    line1->setStyleSheet("font-size:14pt");
    appNameLayout1->addWidget(line1);
    appNameLayout1->addStretch();

	QHBoxLayout* appNameLayout2 = new QHBoxLayout;
	mainLayout->addLayout(appNameLayout2);
	appNameLayout2->addStretch();
	QLabel* line2 = new QLabel("KRAKEEN.one", this);
	line2->setStyleSheet("font-size:10pt");
	appNameLayout2->addWidget(line2);
	appNameLayout2->addStretch();

    mainLayout->addSpacing(100);

    QHBoxLayout* titleLayout = new QHBoxLayout;
    mainLayout->addLayout(titleLayout);
    titleLayout->addStretch();
    QLabel* title = new QLabel("ВВЕДИТЕ ПАРОЛЬ");
    titleLayout->addWidget(title);
    titleLayout->addStretch();


    QHBoxLayout* passwordLineLayout = new QHBoxLayout;
    passwordLineEdit_ = new QLineEdit;
    passwordLineLayout->addStretch();
    passwordLineLayout->addWidget(passwordLineEdit_);
    passwordLineLayout->addStretch();
    mainLayout->addLayout(passwordLineLayout);

    passwordLineEdit_->setFrame(false);
    passwordLineEdit_->setFixedSize(220, 30);
    passwordLineEdit_->setEchoMode(QLineEdit::EchoMode::Password);

    mainLayout->addSpacing(20);

    QHBoxLayout* loginButtonLayout = new QHBoxLayout;
    mainLayout->addLayout(loginButtonLayout);

    loginButtonLayout->addStretch();

    loginButton_ = new QPushButton("ВОЙТИ");
    loginButtonLayout->addWidget(loginButton_);
    loginButton_->setFixedSize(50, 30);
    loginButtonLayout->addStretch();

    mainLayout->addStretch();

    connect(passwordLineEdit_, &QLineEdit::returnPressed, [=]() { emit passwordAttempted(passwordLineEdit_->text()); passwordLineEdit_->clear(); });
    connect(loginButton_, &QPushButton::clicked, [=]() { emit passwordAttempted(passwordLineEdit_->text()); passwordLineEdit_->clear(); });

}

void EnterPasswordFrame::closeEvent(QCloseEvent* event)
{
	event->ignore();
	this->hide();
}
