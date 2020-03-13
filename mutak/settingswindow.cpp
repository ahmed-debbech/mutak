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
    this->rsw.currentWindowIndex = 1;
    this->rsw.previousWindowIndex = 4;
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::on_logout_button_clicked(){
    if(runningWeb == false){
     delete user;
        this->rsw.currentWindowIndex = 0;
        this->rsw.previousWindowIndex = 4;
    ui->stackedWidget->setCurrentIndex(0); // back to login window
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Warning"),
        QObject::tr("Please wait until Mutak is done using internet and try again."), QMessageBox::Ok);
    }
}
void MainWindow::on_delete_history_clicked(){
    QDir q = dbapi->getUserDir();
    QMessageBox::StandardButton resBtn = QMessageBox::critical(nullptr, QObject::tr("Warning"),
    QObject::tr("Are you sure you want to delete this user's saved history? \n NO UNDO!!"),QMessageBox::Yes | QMessageBox::No);
    if (resBtn == QMessageBox::Yes) {
     q.removeRecursively();
    }
}
void MainWindow :: on_helpsettings_clicked(){

}
