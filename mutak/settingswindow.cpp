#include <QDesktopServices>
#include <iostream>
#include <QMessageBox>
#include <QtNetwork>
#include <QStringRef>
#include <QPixmap>
#include <QWidget>
#include <QDateTime>
#include <QTimeZone>
#include <QScrollBar>

#include "user.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_backFromSettings_clicked(){
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::on_logout_button_clicked(){
    if(runningWeb == false){
     delete user;
    ui->stackedWidget->setCurrentIndex(0); // back to login window
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Warning"),
        QObject::tr("Please wait until Mutak is done using internet and try again."), QMessageBox::Ok);
    }
}
void MainWindow::on_delete_history_clicked(){
    QDir q = dbapi->getUserDir();
    q.cdUp();
    q.rmdir("db");
}
