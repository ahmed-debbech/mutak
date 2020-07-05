/*
    Copyright (c) 2020 Ahmed Debbech

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
 */
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
    this->windowsCursor.previousWindowIndex = ui->stackedWidget->currentIndex();
    this->windowsCursor.currentWindowIndex = 1;
    ui->stackedWidget->setCurrentIndex(1);
}
void MainWindow::setAutoRefreshTime(){
    QFile userSettingsFile;
    userSettingsFile.setFileName(dbapi->getUserSettingsPath());
    if(userSettingsFile.exists() == true){
        if (userSettingsFile.open(QIODevice::ReadOnly | QIODevice::Text)){
            if(!userSettingsFile.atEnd()){
                  QByteArray arr = userSettingsFile.readLine();
                  cout << arr.toStdString() << endl;
                  long int y = arr.toInt();
                  switch(y){
                  case 900000:
                    ui->auto_refresh->setCurrentIndex(0);
                      break;
                  case 1800000:
                      ui->auto_refresh->setCurrentIndex(1);
                      break;
                case 2700000:
                    ui->auto_refresh->setCurrentIndex(2);
                  break;
                  case 3600000: ui->auto_refresh->setCurrentIndex(3);
                      break;
                  case 7200000: ui->auto_refresh->setCurrentIndex(4);
                      break;
                   case 0:
                      ui->auto_refresh->setCurrentIndex(5);
                      break;
                  }
            }else{
                cout << "enp;ty" << endl;
            }
        }else{
            QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("Can not read auto-refresh value!"), QMessageBox::Ok);
        }
    }
    userSettingsFile.close();
}
void MainWindow::on_logout_button_clicked(){
    if(runningWeb == false){
        delete user;
        this->windowsCursor.previousWindowIndex = ui->stackedWidget->currentIndex();
        this->windowsCursor.currentWindowIndex = 0;
    ui->stackedWidget->setCurrentIndex(0); // back to login window
    disconnect(timer, SIGNAL(timeout()), this, SLOT(on_refresh_button_clicked()));
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Warning"),
        QObject::tr("Please wait until Mutak is done using internet and try again."), QMessageBox::Ok);
    }
}
void MainWindow::on_delete_history_clicked(){
    QDir q = dbapi->getUserDir();
    QMessageBox::StandardButton resBtn = QMessageBox::critical(nullptr, QObject::tr("Warning"),
    QObject::tr("Are you sure you want to delete this user's saved history? \n All saved tracks will be lost (NO UNDO!!)"),QMessageBox::Yes | QMessageBox::No);
    if (resBtn == QMessageBox::Yes) {
     q.removeRecursively();
    }
}
void MainWindow :: on_aboutsettings_clicked(){
    this->on_aboutButton_clicked();
}
void MainWindow :: on_helpsettings_clicked(){
    this->on_helpButton_clicked();
}
