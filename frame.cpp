#include "frame.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

Frame::Frame(QSharedPointer<QSettings> settings, McuInData* mcuInData, McuOutData* mcuOutData, QWidget *parent) : QWidget(parent), settings_(settings), mcuInData_(mcuInData), mcuOutData_(mcuOutData)
{
    setStyleSheet("QLabel{color:#ffffff}"
                  "QPushButton{border-style:solid; border-width:1px; border-color:#0070c0; color:#ffffff; background:#0070c0}"
                  "QPushButton:pressed{border-style:solid; border-width:1px; border-color:#444444; color:#ffffff; background:#0070c0}"
                  "QLineEdit,QComboBox{color:#f0f0f0; background:#595959; border-style:none}"
                  "QSpinBox{font-size:12pt; color:#ffffff; background:#595959}");
}

void Frame::refresh()
{

}

void Frame::setControlsEnabled(bool state)
{
}

void Frame::addMainLayout(QLayout *layout)
{
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addStretch();
    hLayout->addLayout(layout);
    hLayout->addStretch();

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addStretch();
    vLayout->addLayout(hLayout);
    vLayout->addStretch();

    setLayout(vLayout);
}
