#include "forms/main/mainwindow.h"

#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //Download the translation of the program according to the system language from resource
    QTranslator translator;
    translator.load(QString(":/translations/minishop_")+QLocale::system().name()+".qm");
    a.installTranslator(&translator);

    MainWindow w;
    w.show();
    return a.exec();
}
