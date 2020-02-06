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
    ui->wait_label->setHidden(true);
    dbapi = new DatabaseAPI();
    runningWeb = false;
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
void MainWindow::closeEvent (QCloseEvent *event){
    if(runningWeb == true){
        QMessageBox::StandardButton resBtn = QMessageBox::critical(nullptr, QObject::tr("Warning"),
        QObject::tr("Are you sure you want to exit?\n Mutak is retriving data."), QMessageBox::Yes);
        if (resBtn != QMessageBox::Yes) {
            event->ignore();
        } else {
            event->accept();
        }
    }else{
        event->accept();
    }
}
void MainWindow::addToList(){
    vector<Track> t = dbapi->retriveFromDB(); //dataaaa
    vector <WidgetItem*> widitem;
    //list all the items in list
    for(unsigned int i=t.size(); (i>0); i--){
         WidgetItem *theWidgetItem = nullptr;
        //prepare the item and fill it with data
        theWidgetItem = new WidgetItem(t[i-1]);
        QListWidgetItem * lwi = new QListWidgetItem(ui->listWidget);
        ui->listWidget->addItem(lwi);
        lwi->setSizeHint (theWidgetItem->sizeHint());
        widitem.push_back(theWidgetItem); // we store the widget in individual vector to use it back
        ui->listWidget->setItemWidget(lwi, theWidgetItem);
        ui->countText->setText("Please Wait...");
        ui->listWidget->setCursor(QCursor(Qt::BusyCursor));
    }

    //then retrive each photo for each track and update the item
    bool theresInternet = true;
    for(unsigned int i=t.size(); (theresInternet == true) && (i>0); i--){
         theresInternet = this->checkForInternet();
        if(theresInternet == true){
            runningWeb = true;
            QString link = t[i-1].getID();

            //request the image of each track
            QJsonObject root = this->getFromEndPoint(QUrl("https://api.spotify.com/v1/tracks?ids="+link));
            root = (root.value("tracks").toArray().at(0)).toObject();
            root = root.value("album").toObject();
            QString download = (root.value("images").toArray().at(2)).toObject().value("url").toString();
           retrivePhotosThread rpt (download);
            rpt.run(widitem[t.size()-i]);
            ui->countText->setText("Please Wait... Downloading photos");
            ui->listWidget->setCursor(QCursor(Qt::BusyCursor));
        }else{
            QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("An error occured in retriving photos."), QMessageBox::Ok);
        }
    }
    runningWeb = false;
    ui->listWidget->setCursor(QCursor(Qt::ArrowCursor));
    //get the local date and time in sys
    QDateTime UTC(QDateTime::currentDateTimeUtc());
    QDateTime local = QDateTime(UTC.date(), UTC.time(), Qt::UTC).toLocalTime();
    int count = ui->listWidget->count();
    if(count != 0){
        ui->countText->setText("You've listened to " + QString::number(count)+ " tracks" + " on " +  local.date().toString());
    }else{
        ui->countText->setText("No Tracks");
    }
}
//=================================SIGNALS=======================================
void MainWindow :: isGranted(){
    if(auth.getAuthObject()->status() == QAbstractOAuth::Status::Granted){
        QString Token = auth.getAuthObject()->token();
        QString refToken = auth.getAuthObject()->refreshToken();

        QJsonObject root = getFromEndPoint(QUrl("https://api.spotify.com/v1/me"));
        if(root.empty() == false){
            //passing to the next interface after login
            ui->wait_label->setHidden(true);
            ui->stackedWidget->setCurrentIndex(1);

            this->user = new User(root, Token, refToken);
            this->user->printOnUI(this->getUi());

            //check if the folder of user exists
            dbapi->prepareUserDir(root.value("id").toString());
            //check for files in the current sys date
            dbapi->prepareUserFiles(user->getId());
        }else{
            QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("Could not retrive account data."), QMessageBox::Ok);
            ui->stackedWidget->setCurrentIndex(0);
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
    ui->wait_label->setHidden(false);
    if (this->checkForInternet() == true){
            auth.getAuthObject()->grant();
    }else{
        ui->stackedWidget->setCurrentIndex(2);
    }
}
