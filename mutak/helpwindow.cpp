#include <QDesktopServices>
#include <iostream>
#include <QtNetwork>
#include <QWidget>

#include "ui_mainwindow.h"
#include "mainwindow.h"


void MainWindow :: on_gobackHelp_clicked(){
       ui->stackedWidget->setCurrentIndex(this->windowsCursor.previousWindowIndex);
       this->windowsCursor.currentWindowIndex = this->windowsCursor.previousWindowIndex;
}

