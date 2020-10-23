#include "enterpasswordframe.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "mainwidget.h"

EnterPasswordFrame::EnterPasswordFrame(QWidget* parent) : QWidget(parent)
{
    setStyleSheet(
        "QWidget{background-color:#205867}"
        "QLabel{color:#ffffff}"
        "QPushButton{border-style:solid; border-width:1px; border-color:#0070c0; color:#ffffff; background:#0070c0}"
        "QPushButton:pressed{border-style:solid; border-width:1px; border-color:#444444; color:#ffffff; background:#0070c0}"
        "QLineEdit,QComboBox{color:#333333; background:#f0f0f0}"
       );

    QVBoxLayout* mainLayout = new QVBoxLayout;

    QHBoxLayout* hLayout = new QHBoxLayout;
    hLayout->addStretch();
    hLayout->addLayout(mainLayout);
    hLayout->addStretch();

    QVBoxLayout* vLayout = new QVBoxLayout;
    vLayout->addStretch();
    vLayout->addLayout(hLayout);
    vLayout->addStretch();

    setLayout(vLayout);

    //---

    QHBoxLayout* titleLayout = new QHBoxLayout;
    mainLayout->addLayout(titleLayout);
    titleLayout->addStretch();
    QLabel* title = new QLabel("ВВЕДИТЕ ПАРОЛЬ");
    titleLayout->addWidget(title);
    titleLayout->addStretch();

    passwordLineEdit_ = new QLineEdit;
    mainLayout->addWidget(passwordLineEdit_);

    passwordLineEdit_->setFrame(false);
    passwordLineEdit_->setFixedSize(220, 30);
    passwordLineEdit_->setEchoMode(QLineEdit::EchoMode::Password);

    mainLayout->addSpacing(30);

    QHBoxLayout* loginButtonLayout = new QHBoxLayout;
    mainLayout->addLayout(loginButtonLayout);

    loginButtonLayout->addStretch();

    loginButton_ = new QPushButton("ВОЙТИ");
    loginButtonLayout->addWidget(loginButton_);
    loginButton_->setFixedSize(50, 30);

    loginButtonLayout->addStretch();

    connect(passwordLineEdit_, &QLineEdit::returnPressed, [=]() { emit passwordAttempted(passwordLineEdit_->text()); passwordLineEdit_->clear(); });
    connect(loginButton_, &QPushButton::clicked, [=]() { emit passwordAttempted(passwordLineEdit_->text()); passwordLineEdit_->clear(); });

}

void EnterPasswordFrame::closeEvent(QCloseEvent* event)
{
	event->ignore();
	this->hide();
}
