#include <QDesktopServices>
#include <iostream>
#include <QOAuth2AuthorizationCodeFlow>
#include <QMessageBox>
#include <QtNetwork>
#include <QStringRef>
#include <QPixmap>
#include <QListWidgetItem>
#include <QWidget>
#include <QDateTime>
#include <QTimeZone>
#include <QScrollBar>
#include <QSslSocket>

#include "retrivephotosthread.h"
#include "widgetitem.h"
#include "user.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authorizer.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this); // init all GUI

    //set icon
    this->setWindowIcon(QIcon("://resources/spotifyico.png"));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_refresh_button_clicked()));
    //init window cursors;
    this->windowsCursor.currentWindowIndex = 0;
    this->windowsCursor.previousWindowIndex = -1;

    //preparing the customization of widgets
    this->setWindowTitle("Mutak");
    ui->calendarWidget->setHidden(true);
    ui->navNext->setDisabled(true);
    ui->wait_label->setHidden(true);

    ui->listWidget->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {\nborder: 2px solid black;\nbackground: grey;\n}");
    ui->listWidget->setStyleSheet("QListView::item:selected {background-image: #1db954; background-color: #1db954;padding: 0px;color: black;}\n"
                                  "QListView::item:hover{background-image: #202020; background-color: #202020;padding: 0px; color: black;}");
    dbapi = new DatabaseAPI();
    runningWeb = false;
    stopOnClose = false;
    //get date and time of sys to name the file after it (if file doesnt exist)
    QDateTime UTC(QDateTime::currentDateTimeUtc());
    QDateTime local = QDateTime(UTC.date(), UTC.time(), Qt::UTC).toLocalTime();
    int y,m,d;
    local.date().getDate( &y, &m, &d);
    QDate q; q.setDate(y,m,d);
    ui->calendarWidget->setMaximumDate(q);
    this->currentPageDate = local.date();
    QString h = QString::number(d) + "-" +QString::number(m) + "-" + QString::number(y);

    //setting icon to buttons in UI
    QPixmap pix("://resources/spotifyico.png");
    pix = pix.scaled(128,128,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->logo->setPixmap(pix);
    ui->backFromSettings->setIcon(QPixmap("://resources/leftArrow.png"));
    ui->cautionImage->setPixmap(QPixmap("://resources/caution.png"));

    ui->helpButton->setIcon(QPixmap("://resources/help.png"));
    ui->aboutButton->setIcon(QPixmap("://resources/about.png"));
    ui->navNext->setIcon(QPixmap("://resources/rightArrow.png"));
    ui->navPrev->setIcon(QPixmap("://resources/leftArrow.png"));
    ui->nav->setIcon(QPixmap("://resources/calendar.png"));
    ui->confirm->setIcon(QPixmap("://resources/tick.png"));
    ui->dateName->setText(h);

  //initialize the about section window
    ui->twitter->setIcon(QPixmap("://resources/twitter.png"));
    ui->linkedin->setIcon(QPixmap("://resources/linkedin.png"));
    ui->github->setIcon(QPixmap("://resources/github.png"));
 //end init about section


    //start authorization stuff..
    auth.setValues();
    auth.connectToBrowser();
    connect(auth.getAuthObject(), &QOAuth2AuthorizationCodeFlow::granted,
                this, &MainWindow::isGranted);
}

MainWindow::~MainWindow(){
    delete ui;
    delete user;
    delete dbapi;
    delete timer;
}

QJsonObject  MainWindow:: getFromEndPoint(const QUrl &q){
    QJsonObject root;
    QEventLoop loop; // to never quit the function untill the reply is finished
    QTimer timer;    // timer for time out when no response
    timer.setSingleShot(true);
    auto reply = auth.getAuthObject()->get(q);
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));

    connect(reply, &QNetworkReply::finished, [&root, reply, this]() { //this is a lambda fun
        if (reply->error() != QNetworkReply::NoError) {
            QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("An error occured while retriving data from server!"), QMessageBox::Ok);
        }else{
            QByteArray data = reply->readAll();
            QJsonDocument document = QJsonDocument::fromJson(data);
            root = document.object();
        }
        reply->deleteLater();
    });
    timer.start(8000);  // use miliseconds
    loop.exec();
    /* If the timer ended before the reply from the net then there's no internet if not then
     * the response came before the timer timed out eventually there's internet*/
    if(timer.isActive() == true){ //check if the timer is still running
        timer.stop();
        if (reply->bytesAvailable()){
            if(root.contains("error") == true){
                auth.getAuthObject()->refreshAccessToken();
                user->setToken(auth.getAuthObject()->token());
                QMessageBox::critical(nullptr, QObject::tr("Error"),
                QObject::tr("An error occured while retriving data from server!"), QMessageBox::Ok);
            }else{
                return root;
            }
        }
    }else{
        disconnect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        disconnect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
        reply->abort();
    }
    return root;
}

bool MainWindow::checkForInternet(){
    QNetworkAccessManager nam;
    QNetworkRequest req(QUrl("https://www.google.com"));
    if(QSslSocket::supportsSsl() == false){
        QMessageBox::critical(nullptr, QObject::tr("Error"),
        QObject::tr("no ssl"), QMessageBox::Ok);
        return false;
    }
    QNetworkReply* reply = nam.get(req);
    QEventLoop loop;
    QTimer timer;    // timer for time out when no response
    timer.setSingleShot(true);
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    timer.start(8000);  // use miliseconds
    loop.exec();
    /* If the timer ended before the reply from the net then there's no internet if not then
     * the response came before the timer times out eventually there's internet*/
    if(timer.isActive() == true){ //check if the timer still running
        timer.stop();
        if (reply->bytesAvailable()){
            QString oo = reply->errorString();
            QByteArray ba = oo.toLocal8Bit();
              const char *ff = ba.data();
            QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr(ff), QMessageBox::Ok);
            QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("thers conx"), QMessageBox::Ok);
                return true;
        }else{//
            if(reply->error() == QNetworkReply::NoError){
                QString oo = reply->errorString();
                QByteArray ba = oo.toLocal8Bit();
                  const char *ff = ba.data();
                QMessageBox::critical(nullptr, QObject::tr("Error"),
                QObject::tr(ff), QMessageBox::Ok);
                QMessageBox::critical(nullptr, QObject::tr("Error"),
                QObject::tr("noo errors"), QMessageBox::Ok);
            }else{
                disconnect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                disconnect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
                QString oo = reply->errorString();
                QByteArray ba = oo.toLocal8Bit();
                  const char *ff = ba.data();
                QMessageBox::critical(nullptr, QObject::tr("Error"),
                QObject::tr(ff), QMessageBox::Ok);
                reply->abort();
            QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("thers error"), QMessageBox::Ok);
            }
        }
    }else{
        disconnect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        disconnect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
        reply->abort();
        QMessageBox::critical(nullptr, QObject::tr("Error"),
        QObject::tr("timer aborted"), QMessageBox::Ok);
        return false;
    }
    QMessageBox::critical(nullptr, QObject::tr("Error"),
    QObject::tr("last return"), QMessageBox::Ok);
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
   if(dbapi->sendToDB(tracks) == true){//send to database to save
    vector<Track> t = dbapi->retriveFromDB(); //dataaaa
    this->addToList(t);
   }
}
void MainWindow::closeEvent (QCloseEvent *event){
    if(runningWeb == true){
        QMessageBox::StandardButton resBtn = QMessageBox::critical(nullptr, QObject::tr("Warning"),
        QObject::tr("Are you sure you want to exit?\n Mutak is still retriving data."),QMessageBox::Yes | QMessageBox::No);
        if (resBtn != QMessageBox::Yes) {
            event->ignore();
        } else {
            stopOnClose = true;
            if(runningThreads.size() > 0){
                for(int i=0; i<=runningThreads.size()-1; i++){
                    delete runningThreads[i];
                }
            }
            event->accept();
        }
    }else{
        event->accept();
    }
}
void MainWindow::addToList(vector <Track> t){
    ui->listWidget->clear();
    ui->confirm->setEnabled(false);
    ui->navPrev->setEnabled(false);
    ui->navNext->setEnabled(false);

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
            qDebug() << stopOnClose;
            if(stopOnClose == false){
            //request the image of each track
            QJsonObject root = this->getFromEndPoint(QUrl("https://api.spotify.com/v1/tracks?ids="+link));
            root = (root.value("tracks").toArray().at(0)).toObject();
            root = root.value("album").toObject();
            QString download = (root.value("images").toArray().at(2)).toObject().value("url").toString();
           retrivePhotosThread * rpt  = new retrivePhotosThread(download, widitem[t.size()-i]);
           runningThreads.push_back(rpt);
           connect(rpt, SIGNAL(finished()), this, SLOT(delete_threads(rpt)));
           rpt->start();
            ui->countText->setText("Please Wait... Downloading photos");
            ui->listWidget->setCursor(QCursor(Qt::BusyCursor));
            }else{
                break;
            }
        }else{
            QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("Something went wrong while retriving tracks photos."), QMessageBox::Ok);
        }
    }
    runningWeb = false;
    ui->refresh_button->setEnabled(true);
    ui->listWidget->setCursor(QCursor(Qt::ArrowCursor));
    //get the local date and time in sys
    QDateTime UTC(QDateTime::currentDateTimeUtc());
    QDateTime local = QDateTime(UTC.date(), UTC.time(), Qt::UTC).toLocalTime();
    int count = ui->listWidget->count();
    if(count != 0){
        ui->countText->setText("You've listened to " + QString::number(count)+ " tracks" + " on " +   ui->dateName->text());
    }else{
        ui->countText->setText("No Tracks");
    }
    ui->confirm->setEnabled(true);
    ui->navPrev->setEnabled(true);
    int y,m,d;
    local.date().getDate( &y, &m, &d);
    QString date = QString::number(d) + "-" + QString::number(m) + "-" + QString::number(y);
    if(date == ui->dateName->text()){
        ui->navNext->setEnabled(false);
    }else{
        ui->navNext->setEnabled(true);
    }
}
//=================================SIGNALS=======================================
void MainWindow :: isGranted(){
    if(auth.getAuthObject()->status() == QAbstractOAuth::Status::Granted){
        QString Token = auth.getAuthObject()->token();
        QString refToken = auth.getAuthObject()->refreshToken();
        QMessageBox::critical(nullptr, QObject::tr("Error"),
        QObject::tr("granted with token"), QMessageBox::Ok);
        QJsonObject root = getFromEndPoint(QUrl("https://api.spotify.com/v1/me"));
        if(root.empty() == false){
            //passing to the next interface after login
            ui->wait_label->setHidden(true);
            this->windowsCursor.previousWindowIndex = ui->stackedWidget->currentIndex();
            this->windowsCursor.currentWindowIndex = 1;
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
            this->windowsCursor.previousWindowIndex = ui->stackedWidget->currentIndex();
            this->windowsCursor.currentWindowIndex = 0;
            ui->stackedWidget->setCurrentIndex(0);
        }
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Error"),
        QObject::tr("not gtanted"), QMessageBox::Ok);
    }
}
//=================================SLOTS ========================================
void MainWindow :: delete_threads(retrivePhotosThread * i){
    disconnect(i, SIGNAL(finished()), this, SLOT(delete_threads()));
    delete i;
}
void MainWindow::on_refresh_button_clicked(){
    ui->refresh_button->setEnabled(false);
    timer->start(1500000);
    //get date and time of sys to name the file after it (if file doesnt exist)
    QDateTime UTC(QDateTime::currentDateTimeUtc());
    QDateTime local = QDateTime(UTC.date(), UTC.time(), Qt::UTC).toLocalTime();
    int y,m,d;
    local.date().getDate( &y, &m, &d);
    QString h = QString::number(d) + "-" +QString::number(m) + "-" + QString::number(y);
    ui->dateName->setText(h);

    if(this->checkForInternet() == true){
        ui->listWidget->clear();
        QJsonObject root = getFromEndPoint(QUrl("https://api.spotify.com/v1/me/player/recently-played?limit=50"));
        this->dataToTracksObjects(root);
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Error"),
        QObject::tr("Could not retrive data due to interruption.\nPlease check your internet connection and try again"), QMessageBox::Ok);
        ui->refresh_button->setEnabled(true);
    }
}
void MainWindow::on_settings_button_clicked(){
    this->windowsCursor.previousWindowIndex = ui->stackedWidget->currentIndex();
    this->windowsCursor.currentWindowIndex = 4;
 ui->stackedWidget->setCurrentIndex(4);
}
void MainWindow:: on_refresh_retriv_clicked(){
    this->on_loginButton_clicked();
}
void MainWindow::on_loginButton_clicked(){
    ui->wait_label->setHidden(false);
    ui->loginButton->setEnabled(false);
    if (this->checkForInternet() == true){
        QMessageBox::critical(nullptr, QObject::tr("Error"),
        QObject::tr("thers conx"), QMessageBox::Ok);
            auth.getAuthObject()->grant();
    }else{
        this->windowsCursor.previousWindowIndex = ui->stackedWidget->currentIndex();
        this->windowsCursor.currentWindowIndex = 2;
        ui->stackedWidget->setCurrentIndex(2);
    }
    ui->loginButton->setEnabled(true);
}

void MainWindow::on_navPrev_clicked(){
    this->currentPageDate = this->currentPageDate.addDays(-1);
    int y,m,d;
    currentPageDate.getDate( &y, &m, &d);
    QString date = QString::number(d) + "-" + QString::number(m) + "-" + QString::number(y);
    ui->dateName->setText(date);

    //check when to disable and enable the navNext button
    QDateTime UTC(QDateTime::currentDateTimeUtc());
    QDateTime local = QDateTime(UTC.date(), UTC.time(), Qt::UTC).toLocalTime();
    local.date().getDate( &y, &m, &d);
    date = QString::number(d) + "-" + QString::number(m) + "-" + QString::number(y);
    if(date == ui->dateName->text()){
        ui->navNext->setEnabled(false);
    }else{
        ui->navNext->setEnabled(true);
    }
}
void MainWindow::on_navNext_clicked(){
    //check when to disable and enable the navNext button
    QDateTime UTC(QDateTime::currentDateTimeUtc());
    QDateTime local = QDateTime(UTC.date(), UTC.time(), Qt::UTC).toLocalTime();
    int y,m,d;
    QString date;
    local.date().getDate( &y, &m, &d);
    date = QString::number(d) + "-" + QString::number(m) + "-" + QString::number(y);
    if(date == ui->dateName->text()){
        ui->navNext->setEnabled(false);
    }else{
        this->currentPageDate = this->currentPageDate.addDays(1);
        currentPageDate.getDate( &y, &m, &d);
        date = QString::number(d) + "-" + QString::number(m) + "-" + QString::number(y);
        ui->dateName->setText(date);
        ui->navNext->setEnabled(true);
    }
}
void MainWindow::on_confirm_clicked(){
    ui->calendarWidget->setHidden(true);
    try{
        vector <Track> t = dbapi->retriveFromDB(ui->dateName->text()+".mu");
        ui->listWidget->clear();
        this->addToList(t);
    }catch(QString s){
        ui->listWidget->clear();
        ui->countText->setText("No Tracks for " + ui->dateName->text());
    }
}

void MainWindow::on_nav_clicked(){
    if(ui->calendarWidget->isHidden() == true){
        ui->calendarWidget->setHidden(false);
    }else{
        ui->calendarWidget->setHidden(true);
    }
}

void MainWindow::on_calendarWidget_selectionChanged(){
    QDate d = ui->calendarWidget->selectedDate();
    int y,m,day;
    d.getDate(&y, &m, &day);
    QString g = QString::number(day) + "-" + QString::number(m) + "-" + QString::number(y);
    ui->dateName->setText(g);
    this->currentPageDate = d;
}
void MainWindow :: on_aboutButton_clicked(){
    this->windowsCursor.previousWindowIndex = ui->stackedWidget->currentIndex();
    this->windowsCursor.currentWindowIndex = 3;
    ui->stackedWidget->setCurrentIndex(3);
}
void MainWindow :: on_helpButton_clicked(){
    this->windowsCursor.previousWindowIndex = ui->stackedWidget->currentIndex();
    this->windowsCursor.currentWindowIndex = 5;
    ui->stackedWidget->setCurrentIndex(5);
}

