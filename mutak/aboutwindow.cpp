#include <QDesktopServices>
#include <iostream>
#include <QtNetwork>
#include <QWidget>

#include "ui_mainwindow.h"
#include "mainwindow.h"


void MainWindow :: on_gobackAbout_clicked(){
       ui->stackedWidget->setCurrentIndex(this->rsw.previousWindowIndex);
       this->rsw.currentWindowIndex = this->rsw.previousWindowIndex;
}

void MainWindow::on_twitter_clicked(){
     QDesktopServices::openUrl(QUrl("https://twitter.com/AhmedDebb", QUrl::TolerantMode));
}

void MainWindow::on_linkedin_clicked(){
    QDesktopServices::openUrl(QUrl("https://www.linkedin.com/in/ahmed-debbech-90b834179/", QUrl::TolerantMode));
}
void MainWindow::on_github_clicked(){
     QDesktopServices::openUrl(QUrl("https://github.com/ahmed-debbech/mutak", QUrl::TolerantMode));
}
void MainWindow :: on_website_clicked(){
    QDesktopServices::openUrl(QUrl("https://themutak.000webhostapp.com/", QUrl::TolerantMode));
}
