#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authorizer.h"
#include <QDesktopServices>
#include <iostream>
#include <QOAuth2AuthorizationCodeFlow>
#include <QMessageBox>
#include <QtNetwork>
#include "user.h"
#include <QStringRef>
#include "photodownloader.h"
#include <QPixmap>
#include <QListWidgetItem>

void MainWindow::addToList(){
    for(unsigned int i=0; i<= tracks.size()-1; i++){
        QString link = tracks[i].getLink();
        QStringRef substr(&link, 31, ((tracks[i].getLink()).size()-1) - 30);
        //request the image of each track
        QJsonObject root = this->getFromEndPoint(QUrl("https://api.spotify.com/v1/tracks?ids="+substr));
        root = (root.value("tracks").toArray().at(0)).toObject();
        root = root.value("album").toObject();
        QString download = (root.value("images").toArray().at(2)).toObject().value("url").toString();
        std::cout << download.toStdString() <<std::endl;
        //prepare and resize each image
       /*photoDownloader * pd = new photoDownloader(download);
        QPixmap pix;
        pix.loadFromData(pd->downloadedData());
        pix = pix.scaled(32,32,Qt::KeepAspectRatio,Qt::SmoothTransformation);*/
    }
    QListWidgetItem * lwi = NULL;
    ui->listWidget->addItem(lwi);
}
QJsonObject  MainWindow:: getFromEndPoint(const QUrl &q){
    QJsonObject root;
    QEventLoop loop; // to never quit the function untill the reply is finished
    auto reply = auth.getAuthObject()->get(q);
    connect(reply, &QNetworkReply::finished, [&root, reply, this]() { //this is a lambda fun
        if (reply->error() != QNetworkReply::NoError) {
            QMessageBox::critical(nullptr, QObject::tr("Info"),
            QObject::tr("An error occured while retriving data!"), QMessageBox::Ok);
            ui->stackedWidget->setCurrentIndex(2);
        }else{
            QByteArray data = reply->readAll();
            //std::cout << "json doc: " << data.toStdString() << std::endl;
            QJsonDocument document = QJsonDocument::fromJson(data);
            root = document.object();
        }
        reply->deleteLater();
    });
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    return root;
}
bool MainWindow::checkForInternet(){
    QNetworkAccessManager nam;
    QNetworkRequest req(QUrl("https://www.google.com"));
    QNetworkReply* reply = nam.get(req);
    QEventLoop loop;
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
    if (reply->bytesAvailable()){
            return true;
    }
    return false;
}
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
    delete user;
}

void MainWindow::on_loginButton_clicked(){
    if (this->checkForInternet() == true){
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
        QJsonObject root = getFromEndPoint(QUrl("https://api.spotify.com/v1/me"));
        if(root.empty() == false){
            this->user = new User(root, Token);
            this->user->printOnUI(this->getUi());
        }
    }
}
void MainWindow :: dataToTracksObjects(QJsonObject &data){
    QJsonObject jb = data;
    QJsonArray arr;
    for(int i=0; i <= 49; i++){
        jb = data;
        arr = jb.value("items").toArray();
        jb = (arr.at(i).toObject()).value("track").toObject();
        arr = jb.value("artists").toArray();
        QString artistName = arr.at(0).toObject().value("name").toString();
        QString trackName = jb.value("name").toString();
        double dur = jb.value("duration_ms").toDouble();
        QString play = (data.value("items").toArray()).at(0).toObject().value("played_at").toString();
        jb = jb.value("external_urls").toObject();
        QString link = jb.value("spotify").toString();
        tracks.push_back(Track(trackName,artistName,dur,play,link));
    }
    this->addToList();
}
void MainWindow::on_refresh_button_clicked(){
    if(this->checkForInternet() == true){
        QJsonObject root = getFromEndPoint(QUrl("https://api.spotify.com/v1/me/player/recently-played?limit=50"));
        this->dataToTracksObjects(root);
    }
}
void MainWindow:: on_refresh_retriv_clicked(){
    this->on_loginButton_clicked();
}
