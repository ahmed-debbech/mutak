#include "mainwindow.h"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    foreach (const QString &path, QCoreApplication::libraryPaths())
           std::cout << path.toStdString() <<std::endl;
    MainWindow w;
    w.show();
    return a.exec();
}
