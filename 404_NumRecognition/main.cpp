#include "mainwindow.h"
#include <QApplication>
#include <QLatin1String>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QFile qssFile(":/QSS/qt.qss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        QString qss = QLatin1String(qssFile.readAll());
        qApp->setStyleSheet(qss);
        qssFile.close();
    }

    MainWindow w;
    w.show();

    return a.exec();
}
