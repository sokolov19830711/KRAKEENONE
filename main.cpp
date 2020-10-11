#include <QApplication>
#include "mainwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    w.setFixedSize(1100, 500);
    w.setStyleSheet("background-color:#205867");
    w.show();

    return a.exec();
}
