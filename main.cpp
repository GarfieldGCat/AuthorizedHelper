#include "mainwindows.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator ts;
    ts.load("I18N/zh_cn.qm");
    a.installTranslator(&ts);

    MainWindows w;
    w.show();

    return a.exec();
}
