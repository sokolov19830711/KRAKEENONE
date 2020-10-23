#ifndef ENTERPASSWORDFRAME_H
#define ENTERPASSWORDFRAME_H

#include "frame.h"

#include <QLineEdit>
#include <QPushButton>

class EnterPasswordFrame : public QWidget
{
    Q_OBJECT

public:
    EnterPasswordFrame(QWidget *parent = nullptr);

signals:

    void passwordAttempted(const QString& password);

public slots:

protected:

	void closeEvent(QCloseEvent* event);

private:

    QLineEdit* passwordLineEdit_;
    QPushButton* loginButton_;
};

#endif // ENTERPASSWORDFRAME_H
