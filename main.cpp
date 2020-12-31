#include "MainWindow.h"

#include <QApplication>

#define TYPE_IT_EDITOR

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
