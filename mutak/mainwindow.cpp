#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authorizer.h"
#include <QDesktopServices>
#include <iostream>
#include <QOAuth2AuthorizationCodeFlow>
#include <QMessageBox>
#include <QtNetwork>
#include "user.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auth.setValues();
    auth.connectToBrowser();
    connect(auth.getAuthObject(), &QOAuth2AuthorizationCodeFlow::granted,
                this, &MainWindow::isGranted);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_loginButton_clicked(){
    QNetworkAccessManager nam;
    QNetworkRequest req(QUrl("https://www.google.com"));
    QNetworkReply* reply = nam.get(req);
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    if (reply->bytesAvailable()){
            auth.getAuthObject()->grant();
    }else{
        ui->stackedWidget->setCurrentIndex(2);
    }
}


void MainWindow:: isGranted(){
    if(auth.getAuthObject()->status() == QAbstractOAuth::Status::Granted){
        QString Token = auth.getAuthObject()->token();
        std::cout << Token.toStdString() << std::endl;
        //passing to the next interface after login
        ui->stackedWidget->setCurrentIndex(1);
        auto reply = auth.getAuthObject()->get(QUrl("https://api.spotify.com/v1/me"));
        connect(reply, &QNetworkReply::finished, [=]() {
            if (reply->error() != QNetworkReply::NoError) {
                QMessageBox::critical(nullptr, QObject::tr("Info"),
                QObject::tr("An error occured while retriving data!"), QMessageBox::Ok);
                ui->stackedWidget->setCurrentIndex(2);
            }else{
                QByteArray data = reply->readAll();
                std::cout << "json doc: " << data.toStdString() << std::endl;
                QJsonDocument document = QJsonDocument::fromJson(data);
                QJsonObject root = document.object();
                User u(root, Token);
                u.printOnUI(this->getUi());
            }
            reply->deleteLater();
        });
    }
}
void MainWindow::on_refresh_button_clicked(){

}
void MainWindow:: on_refresh_retriv_clicked(){
    this->on_loginButton_clicked();
}
