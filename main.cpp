#include "views/MainWindow.h"

#include <QApplication>
#include <QFont>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    a.setFont(QFont("Kristen ITC,华文行楷"));

    MainWindow w;
    w.show();
    return a.exec();
}
