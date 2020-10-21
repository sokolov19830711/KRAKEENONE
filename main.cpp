#include <QApplication>
#include "mainwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    w.setFixedSize(1200, 536);
    w.show();

    return a.exec();
}
