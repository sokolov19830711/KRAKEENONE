#include "aboutframe.h"

#include <QFormLayout>

AboutFrame::AboutFrame(QSharedPointer<QSettings> settings, McuInData *mcuInData, McuOutData *mcuOutData, QWidget *parent) : Frame(settings, mcuInData, mcuOutData, parent)
{
    QFormLayout* mainLayout = new QFormLayout;
    addMainLayout(mainLayout);

    enterActivationKeyLabel_ = new QLabel(this);
    enterActivationKeyLabel_->setText("ВВЕДИТЕ КЛЮЧ АКТИВАЦИИ ПРИЛОЖЕНИЯ");

    mainLayout->addRow(enterActivationKeyLabel_);

    activationKey_ = new QLineEdit(this);
    activationKey_->setStyleSheet("font-size:14pt;");
    activationKey_->setAlignment(Qt::AlignCenter);
    activationKey_->setFixedSize(500, 25);
    activationKey_->setText("XXXX-XXXX-XXXX-XXXX");

    activateButton_ = new QPushButton(this);
    activateButton_->setFixedSize(100, 24);
    activateButton_->setText("АКТИВИРОВАТЬ");

    QHBoxLayout* actLayout = new QHBoxLayout;
    actLayout->addWidget(activationKey_);
    actLayout->addWidget(activateButton_);

    mainLayout->addRow(actLayout);

    infoText_ = new QPlainTextEdit(this);
    infoText_->setFixedSize(600, 300);
    infoText_->setStyleSheet("border-style:none; font-size:12pt; color:#ffffff");
    infoText_->setPlainText("Все  исключительные  права  на  данный  программно-аппаратный  комплекс принадлежат  торговым  маркам  PRIMEBOX  и  TRUEDEVICE. "
                        "Пользователю (или  иным  третьим  лицам)  запрещается  менять,  дизассемблировать, декомпилировать,  "
                        "дешифровать  или  проводить  другие  действия  с объектным  кодом  и  аппаратной  частью  данного  комплекса  без"
                        " письменного  согласия  Правообладателя.  Пользователь  не  имеет  права распространять  данный  программно-аппаратный  комплекс, "
                        "воспроизводить и доводить ее до всеобщего сведения в какой-либо форме и  способом  без  письменного  согласия  Правообладателя. "
                        "Невыполнение вышеперечисленных  требований  преследуется  административной  и уголовной ответственностью.");

    infoText_->setReadOnly(true);
    mainLayout->addWidget(new QLabel(this));
    mainLayout->addRow(infoText_);
}
