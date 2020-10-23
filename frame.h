#ifndef FRAME_H
#define FRAME_H

#include <QWidget>
#include <QSettings>

#include "firmware/dataStructures.h"

class Frame : public QWidget
{
    Q_OBJECT
public:

    Frame(QSharedPointer<QSettings> settings, McuInData* mcuInData, McuOutData* mcuOutData, QWidget *parent = nullptr);

    virtual void refresh();

signals:

public slots:

protected:

    QSharedPointer<QSettings> settings_;
    McuInData* mcuInData_;
    McuOutData* mcuOutData_;

    //! Добавляем осонвной layuot кадра, который центрирует виджет в выделенном для него пространстве
    void addMainLayout(QLayout* layout);
};

#endif // FRAME_H
