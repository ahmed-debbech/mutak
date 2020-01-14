#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authorizer.h"
#include <QDesktopServices>
#include <iostream>
#include <QOAuth2AuthorizationCodeFlow>
#include <QMessageBox>
#include <QtNetwork>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QString clientID = "17003af1c95b4506b21dbf98110a6e6f";
   QString clientSecret = "52291278398442e1961f84615d55a097";
    ui->setupUi(this);
    auth.setValues();
    auth.connectToBrowser();
    connect(auth.getAuthObject(), &QOAuth2AuthorizationCodeFlow::granted,
                this, &MainWindow::isGranted);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loginButton_clicked()
{
    QNetworkAccessManager nam;
    QNetworkRequest req(QUrl("https://www.google.com"));
    QNetworkReply* reply = nam.get(req);
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    if (reply->bytesAvailable()){
            auth.getAuthObject()->grant();
        ui->stackedWidget->setCurrentIndex(1);
    }else{
        QMessageBox::critical(this, "Info", "You are not connected to the internet :(");
    }
}


void MainWindow:: isGranted(){

    if(auth.getAuthObject()->status() == QAbstractOAuth::Status::Granted){
        Token = auth.getAuthObject()->token();
        ui->plainTextEdit->appendPlainText(Token);
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Info"),
        QObject::tr("Access denied, Can not access this account!"), QMessageBox::Ok);
    }
}


void MainWindow::on_whoami_clicked(){
    auto reply = auth.getAuthObject()->get(QUrl("https://api.spotify.com/v1/me"));
    connect(reply, &QNetworkReply::finished, [=]() {
    if (reply->error() != QNetworkReply::NoError) {
        std::cout << "error " << reply->errorString().toStdString() << std::endl;
        return;
    }
    QByteArray data = reply->readAll();

    std::cout << "error " << data.toStdString() << std::endl;
    QJsonDocument document = QJsonDocument::fromJson(data);
    QJsonObject root = document.object();

    ui->label_2->setText("Username: " + root.value("id").toString());

    reply->deleteLater();
});
}
