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
#include <QWidget>
#include "widgetitem.h"
#include <QDateTime>
#include <QTimeZone>
#include "retrivephotosthread.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    this->setWindowTitle("Mutak");
    dbapi = new DatabaseAPI();
    auth.setValues();
    auth.connectToBrowser();
    connect(auth.getAuthObject(), &QOAuth2AuthorizationCodeFlow::granted,
                this, &MainWindow::isGranted);
}

MainWindow::~MainWindow(){
    delete ui;
    delete user;
    delete dbapi;
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
    if(root.contains("error") == true){
        auth.getAuthObject()->refreshAccessToken();
        user->setToken(auth.getAuthObject()->token());
        return this->getFromEndPoint(q); //repeat the request
    }
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

void MainWindow :: dataToTracksObjects(QJsonObject &data){
    QJsonObject jb = data, r = data;
    QJsonArray arr;
    for(int i=0; i <= 49; i++){
        jb = data;
        arr = jb.value("items").toArray();
        jb = (arr.at(i).toObject()).value("track").toObject();
        arr = jb.value("artists").toArray();
        QString artistName = arr.at(0).toObject().value("name").toString();
        QString trackName = jb.value("name").toString();
        double dur = jb.value("duration_ms").toDouble();
        QString play = (r.value("items").toArray()).at(i).toObject().value("played_at").toString();

        //timezone conversion to play date
        QString format = "yyyy-MM-ddTHH:mm:ss.zzzZ";
        QDateTime dt = QDateTime::fromString (play, format);
        QDateTime playtimeConverted = QDateTime(dt.date(), dt.time(), Qt::UTC).toLocalTime();

        jb = jb.value("external_urls").toObject();
        QString link = jb.value("spotify").toString();
        QStringRef substr(&link, 31, (link.size()-1) - 30);
        QString l = substr.toString();

         tracks.push_back(Track(trackName,artistName,dur,playtimeConverted.toString(),l));
    }
   dbapi->sendToDB(tracks); //send to database to save
    this->addToList();
}

void MainWindow::addToList(){
    bool quitLoop = false;
    vector<Track> t = dbapi->retriveFromDB();
    for(unsigned int i=t.size(); ((i>0) && (quitLoop == false)); i--){
        if(this->checkForInternet() == true){
            QString link = t[i-1].getID();
            //request the image of each track
            QJsonObject root = this->getFromEndPoint(QUrl("https://api.spotify.com/v1/tracks?ids="+link));
            root = (root.value("tracks").toArray().at(0)).toObject();
            root = root.value("album").toObject();
            QString download = (root.value("images").toArray().at(2)).toObject().value("url").toString();

            //prepare the item and fill it with data
            WidgetItem *theWidgetItem = new WidgetItem(t[i-1]);
            retrivePhotosThread rpt(download);
            rpt.run(theWidgetItem);
            QListWidgetItem * lwi = new QListWidgetItem(ui->listWidget);
            ui->listWidget->addItem(lwi);
            lwi->setSizeHint (theWidgetItem->sizeHint());
            ui->listWidget->setItemWidget(lwi, theWidgetItem);
            ui->countText->setText("Please Wait...");
        }else{
           quitLoop = true;
        }
    }
    if(quitLoop == true){
        ui->stackedWidget->setCurrentIndex(2); //pass to no connection screen
    }else{
        ui->countText->setText(QString::number(ui->listWidget->count())+ " Tracks");
    }
}
//=================================SIGNALS=======================================
void MainWindow :: isGranted(){
    if(auth.getAuthObject()->status() == QAbstractOAuth::Status::Granted){
        QString Token = auth.getAuthObject()->token();
        QString refToken = auth.getAuthObject()->refreshToken();

        //passing to the next interface after login
        ui->stackedWidget->setCurrentIndex(1);
        QJsonObject root = getFromEndPoint(QUrl("https://api.spotify.com/v1/me"));
        if(root.empty() == false){
            //check if the folder of user exists
            dbapi->prepareUserDir(root.value("id").toString());
            //check for files in the current sys date
            dbapi->prepareUserFiles();

            this->user = new User(root, Token, refToken);
            this->user->printOnUI(this->getUi());
        }else{
            QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("Could not retrive account data."), QMessageBox::Ok);
        }
    }
}
//=================================SLOTS ========================================
void MainWindow::on_refresh_button_clicked(){
    if(this->checkForInternet() == true){
        ui->listWidget->clear();
        QJsonObject root = getFromEndPoint(QUrl("https://api.spotify.com/v1/me/player/recently-played?limit=50"));
        this->dataToTracksObjects(root);
    }
}
void MainWindow:: on_refresh_retriv_clicked(){
    this->on_loginButton_clicked();
}
void MainWindow::on_loginButton_clicked(){
    if (this->checkForInternet() == true){
            auth.getAuthObject()->grant();
    }else{
        ui->stackedWidget->setCurrentIndex(2);
    }
}
