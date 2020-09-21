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
#include <dirent.h>
#include <windows.h>
#include <wincred.h>
#include <tchar.h>

#include <QOAuth2AuthorizationCodeFlow>
#include <QMessageBox>
#include <QtNetwork>
#include <QStringRef>
#include <QPixmap>
#include <QDebug>
#include <QListWidgetItem>
#include <QWidget>
#include <QDateTime>
#include <QTimeZone>
#include <QScrollBar>
#include <QSslSocket>
#include <QLibrary>

#include "retrivephotosthread.h"
#include "widgetitem.h"
#include "user.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authorizer.h"
#include "exceptionerror.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this); // init all GUI

    //set icon
    this->setWindowIcon(QIcon("://resources/spotifyico.png"));
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(auto_refresh()));
    //init window cursors;
    this->windowsCursor.currentWindowIndex = 0;
    this->windowsCursor.previousWindowIndex = -1;

    //set signal to slots init
    connect(ui->search_text, &QLineEdit::textChanged, this, &MainWindow::refreshSearch);
    connect(ui->auto_refresh, &QComboBox::currentTextChanged, this, &MainWindow::changeValue);

    //preparing the customization of widgets
    this->setWindowTitle("Mutak");
    ui->calendarWidget->setHidden(true);
    ui->navNext->setDisabled(true);
    ui->wait_label->setHidden(true);
    ui->wait_label2->setHidden(true);
    ui->stop_button->setHidden(true);
    ui->menuBar2->setHidden(true);
    ui->search_list->setHidden(true);
     ui->search_tip->setHidden(true);

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
    //set date for date indicator
    QString str = this->convertDateToQString(q);
    ui->date_ind->setText("These are the songs for: " + str);
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

    //check if mutak remembers the user from vault
    bool k = this->restoreTokens();
    if(k == true){
        //passing to the next interface after login
        ui->wait_label->setHidden(true);
        this->windowsCursor.previousWindowIndex = ui->stackedWidget->currentIndex();
        this->windowsCursor.currentWindowIndex = 1;
        ui->stackedWidget->setCurrentIndex(1);
        auth.getAuthObject()->grant();
        this->isAlreadyGranted();
    }else{
        //else start authorization stuff..
        auth.setValues();
        auth.connectToBrowser();
        connect(auth.getAuthObject(), &QOAuth2AuthorizationCodeFlow::granted,
                    this, &MainWindow::isGranted);
    }
}

MainWindow::~MainWindow(){
    delete ui;
    delete user;
    delete dbapi;
    delete timer;
}

/**
 * @brief MainWindow::setCalendarMarks responsible for coloring the date that have a play history
 * in the database.
 *
 */
void MainWindow :: setCalendarMarks(){
    struct dirent *entry;
    const char * c = dbapi->getUserDir().absolutePath().toStdString().c_str();
    DIR *dir = opendir(c);
    if (dir == NULL) {
        return;
    }
    while ((entry = readdir(dir)) != NULL) {
        cout << entry->d_name << endl;
        if(dbapi->checkFileExistance(entry->d_name) == true){
            int y,m,d;
            sscanf(entry->d_name,"%d-%d-%d.mu", &d,&m,&y);
            QTextCharFormat fmt;
            fmt.setBackground(Qt::yellow);
            ui->calendarWidget->setDateTextFormat(QDate(y,m,d), fmt);
        }
    }
    closedir(dir);
}
/**
 * @brief MainWindow::convertDateToQString this converts a QDate to a string of a passed date
 * @param QDate this is the date that will be converted
 * @return QString a string respresenting the result.
 */
QString MainWindow :: convertDateToQString(QDate q){
    QString res;
    res = res + QString::number(q.day());
    res += " ";
    switch(q.month()){
        case 1: res += "January"; break;
        case 2: res += "Februrary"; break;
        case 3: res += "March"; break;
        case 4: res += "April"; break;
        case 5: res += "May"; break;
        case 6: res += "June"; break;
        case 7: res += "July"; break;
        case 8: res += "August"; break;
        case 9: res += "Septembre"; break;
        case 10: res += "Octobre"; break;
        case 11: res += "Novembre"; break;
         case 12: res += "Decembre"; break;
    }
    res += " ";
    res += QString::number(q.year());
    return res;

}
/**
 * @brief MainWindow::convertDateToQString this converts a date in integers to a string of a passed date
 * This is an overloaded method
 * @param int denoting the day number
 * @param int denoting the month number
 * @param int denoting the year number
 * @return QString a string respresenting the result.
 */
QString MainWindow :: convertDateToQString(int d, int m, int y){
    QString res;
    res = res + QString::number(d);
    res += " ";
    switch(m){
        case 1: res += "January"; break;
        case 2: res += "Februrary"; break;
        case 3: res += "March"; break;
        case 4: res += "April"; break;
        case 5: res += "May"; break;
        case 6: res += "June"; break;
        case 7: res += "July"; break;
        case 8: res += "August"; break;
        case 9: res += "Septembre"; break;
        case 10: res += "Octobre"; break;
        case 11: res += "Novembre"; break;
         case 12: res += "Decembre"; break;
    }
    res += " ";
    res += QString::number(y);
    return res;

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
            ::CredDeleteA("Mutak for Spotify 1", CRED_TYPE_GENERIC, 0);
            ::CredDeleteA("Mutak for Spotify 2", CRED_TYPE_GENERIC, 0);
            QByteArray data = reply->readAll();
            qDebug() <<"THIS IS ERROR: " << data;
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

void MainWindow::checkForInternet(){
    QNetworkAccessManager nam;
    QNetworkRequest req(QUrl("https://www.google.com"));

    if(QSslSocket::supportsSsl() == false){
        throw exceptionError(100, "Could not initialize a secure tunnel over SSL ERROR_CODE_100");
    }
    QNetworkReply* reply = nam.get(req);
    QEventLoop loop;
    QTimer timer;    // timer for time out when no response
    timer.setSingleShot(true);
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    timer.start(10000);  // use miliseconds
    loop.exec();
    /* If the timer ended before the reply from the net then there's no internet if not then
     * the response came before the timer times out eventually there's internet*/
    if(timer.isActive() == true){ //check if the timer still running
        timer.stop();
        if (reply->bytesAvailable()){
                return; // there's internet connection
        }else{
                disconnect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
                disconnect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
                reply->abort();
                throw exceptionError(101, "Connection interrupted with empty response ERROR_CODE_101");
        }
    }else{
        disconnect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
        disconnect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
        reply->abort();
        throw exceptionError(100, "Timemout after no response, timer aborted ERROR_CODE_102");
    }
}
vector<Track> MainWindow::sortByTime(vector<Track> t){
    std::list<Track> l;
    std::vector<Track> tr;
    if(t.size() > 0){
        for(unsigned int i =0; i<=t.size()-1; i++){
            l.push_back(t[i]);
        }
    }
    // we use selection sort algo
    std::list<Track>:: iterator walk = l.begin();
    std::list<Track>:: iterator hold;
    Track swap;
    while(walk != l.end()){
        std::list<Track>:: iterator holder = walk;
        hold = holder++;
        while(hold != l.end()){
            if(walk->getPlayDate().time() > hold->getPlayDate().time()){
                swap = *hold;
                *hold = *walk;
                *walk = swap;
            }
            hold++;
        }
        walk++;
    }
    for(std::list<Track>:: iterator walk = l.begin(); walk != l.end(); walk++){
        tr.push_back(*walk);
    }
    return tr;
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

         tracks.push_back(Track(trackName,artistName,dur,playtimeConverted,l));
    }
   if(dbapi->sendToDB(tracks) == true){//send to database to save
     try{
         vector<Track> t = dbapi->retriveFromDB(); //dataaaa
         this->addToList(t);
       }catch(QString string){
            ui->countText->setText(string);
            throw exceptionError(200, "No tracks yet for today");
       }
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
void MainWindow::getArtworks(vector<Track> t){
    stopOnClose = false;
    bool theresInternet = true;
    for(unsigned int i=t.size(); (theresInternet == true) && (i>0); i--){
         try{
            this->checkForInternet();
         }catch(exceptionError & e){
            theresInternet = false;
            QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr(e.getErrorMsg()), QMessageBox::Ok);
         }
        if(theresInternet == true){
            runningWeb = true;
            QString link = t[i-1].getID();
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
        }
    }
}
void MainWindow::addToList(vector <Track> t){
    t = this->sortByTime(t);
    //this is memory enhancment: we clear the old widget pointers to avoid memory leaks
    if(this->widitem.size() > 0){
        for (int i=0; i<=this->widitem.size()-1; i++) {
           delete widitem[i];
        }
    }
    this->widitem.clear();
    ui->listWidget->clear();
    //end of memory enhancment
    ui->confirm->setEnabled(false);
    ui->navPrev->setEnabled(false);
    ui->navNext->setEnabled(false);
   ui->today->setEnabled(false);
    //list all the items in list
    if(t.size() > 0){
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
        this->getArtworks(t);
    }
    runningWeb = false;
    ui->refresh_button->setHidden(false);
    ui->search_button->setDisabled(false);
    ui->stop_button->setHidden(true);
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
    ui->today->setEnabled(true);
    int y,m,d;
    local.date().getDate( &y, &m, &d);
    QString date = QString::number(d) + "-" + QString::number(m) + "-" + QString::number(y);
    if(date == ui->dateName->text()){
        ui->navNext->setEnabled(false);
    }else{
        ui->navNext->setEnabled(true);
    }
}
/**
 * @brief MainWindow::storeTokens it stores tokens in Windows Credential Manager for remmbering the user each time he/she logins
 * @param token the access token to be stored
 */
void MainWindow :: storeTokens(QString token, QString ref){
    char password[1024];
    strcpy(password,token.toStdString().c_str());
    DWORD cbCreds = (DWORD)strlen(password);
    CREDENTIALW cred ={0};
    cred.Type = CRED_TYPE_GENERIC;
    cred.TargetName = L"Mutak for Spotify 1\0";
    cred.CredentialBlobSize = cbCreds;
    cred.CredentialBlob = (LPBYTE)password;
    cred.Persist = CRED_PERSIST_LOCAL_MACHINE;
    cred.UserName = L"user";
    BOOL ok = ::CredWriteW(&cred, 0);
    if(ok == 1){
        qDebug() << "registered access token" << endl;
    }
    strcpy(password,ref.toStdString().c_str());
    cbCreds = (DWORD)strlen(password);
    cred ={0};
    cred.Type = CRED_TYPE_GENERIC;
    cred.TargetName = L"Mutak for Spotify 2\0";
    cred.CredentialBlobSize = cbCreds;
    cred.CredentialBlob = (LPBYTE)password;
    cred.Persist = CRED_PERSIST_LOCAL_MACHINE;
    cred.UserName = L"user";
    ok = ::CredWriteW(&cred, 0);
    if(ok == 1){
        qDebug() << "registered ref token" << endl;
    }
}
/**
 * @brief MainWindow::restoreTokens it rstores tokens from Windows Credential Manager to use it for authentication.
 */
bool MainWindow :: restoreTokens(){
    PCREDENTIALW pcred, pcred1;
    BOOL ok = ::CredReadW (L"Mutak for Spotify 1", CRED_TYPE_GENERIC, 0, &pcred);
    BOOL ok1 = ::CredReadW (L"Mutak for Spotify 2", CRED_TYPE_GENERIC, 0, &pcred1);
    if(ok == 1 && ok1 == 1){
        QString cv="", ref=""; int i=0;
        do{
            cv += pcred->CredentialBlob[i];
            i++;
        }while(i < pcred->CredentialBlobSize);
        qDebug() << "ACC: " << cv << "\n";
        i=0;
        do{
            ref += pcred1->CredentialBlob[i];
            i++;
        }while(i < pcred1->CredentialBlobSize);
        qDebug() << "ACC: " << ref << "\n";
        this->auth.setValues(cv, ref);
        // must free memory allocated by CredRead()!
        ::CredFree (pcred);
        ::CredFree (pcred1);
        return true;
    }
    return false;
}
void MainWindow :: isAlreadyGranted(){
        QString Token = auth.getAuthObject()->token();
        QString refToken = auth.getAuthObject()->refreshToken();
        QJsonObject root = getFromEndPoint(QUrl("https://api.spotify.com/v1/me"));
        if(root.empty() == false){
            this->user = new User(root, Token, refToken);
            this->user->printOnUI(this->getUi());

            //check if the folder of user exists
            dbapi->prepareUserDir(root.value("id").toString());
            //check for files in the current sys date
            dbapi->prepareUserFiles(user->getId());

            this->setAutoRefreshTime();
        }else{
            QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("Could not retrive account data."), QMessageBox::Ok);
            this->windowsCursor.previousWindowIndex = ui->stackedWidget->currentIndex();
            this->windowsCursor.currentWindowIndex = 0;
            ui->stackedWidget->setCurrentIndex(0);
        }
}
//=================================SIGNALS=======================================
void MainWindow :: isGranted(){
    if(auth.getAuthObject()->status() == QAbstractOAuth::Status::Granted){
        QString Token = auth.getAuthObject()->token();
        QString refToken = auth.getAuthObject()->refreshToken();
        this->storeTokens(Token, refToken);
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

            this->setAutoRefreshTime();
            on_refresh_button_clicked();
        }else{
            QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("Could not retrive account data."), QMessageBox::Ok);
            this->windowsCursor.previousWindowIndex = ui->stackedWidget->currentIndex();
            this->windowsCursor.currentWindowIndex = 0;
            ui->stackedWidget->setCurrentIndex(0);
        }
    }
}
//=================================SLOTS ========================================
void MainWindow :: delete_threads(retrivePhotosThread * i){
    disconnect(i, SIGNAL(finished()), this, SLOT(delete_threads()));
    delete i;
}
void MainWindow::on_stop_button_clicked(){
    stopOnClose = true;
}
void MainWindow::changeValue(){
    QFile userSettingsFile;
    userSettingsFile.setFileName(dbapi->getUserSettingsPath());
    if(userSettingsFile.exists() == true){
        if (userSettingsFile.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream tofile(&userSettingsFile);
            tofile << convertToMS(ui->auto_refresh->currentIndex());
        }else{
            QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("Can not write auto-refresh value!"), QMessageBox::Ok);
        }
    }
    userSettingsFile.close();
}
long int MainWindow :: convertToMS(int index){
    switch(index){
        case 0: timer->stop(); return 900000; //15min
        break;
    case 1: timer->stop(); return 1800000; //30min
        break;
    case 2: timer->stop(); return 2700000; //45min
        break;
    case 3: timer->stop(); return 3600000; //1hr
        break;
    case 4: timer->stop(); return 7200000; //2hr
        break;
    case 5:  return 0;
        break;
    }
    return 0;
}
void MainWindow::auto_refresh(){
    try {
        checkForInternet();
        on_refresh_button_clicked();
    } catch (exceptionError &er) {

    }
}
void MainWindow::on_refresh_button_clicked(){
    ui->refresh_button->setHidden(true);
    ui->stop_button->setHidden(false);
    ui->search_button->setDisabled(true);
    long int time = convertToMS(ui->auto_refresh->currentIndex());
    if(time != 0){
        timer->start(time);
   }else{
         timer->stop();
   }
    //get date and time of sys to name the file after it (if file doesnt exist)
    QDateTime UTC(QDateTime::currentDateTimeUtc());
    QDateTime local = QDateTime(UTC.date(), UTC.time(), Qt::UTC).toLocalTime();
    int y,m,d;
    local.date().getDate( &y, &m, &d);
    ui->date_ind->setText("These are the songs for: " + this->convertDateToQString(d,m,y));
    QString h = QString::number(d) + "-" +QString::number(m) + "-" + QString::number(y);
    ui->dateName->setText(h);
    try{
        this->checkForInternet();
        ui->listWidget->clear();
        QJsonObject root = getFromEndPoint(QUrl("https://api.spotify.com/v1/me/player/recently-played?limit=50"));
        this->dataToTracksObjects(root);
    }catch(exceptionError & e){
        QMessageBox::critical(nullptr, QObject::tr("Error"),
        QObject::tr(e.getErrorMsg()), QMessageBox::Ok);
        ui->refresh_button->setHidden(false);
        ui->stop_button->setHidden(true);
        ui->search_button->setDisabled(false);
    }
}
void MainWindow::on_settings_button_clicked(){
    this->windowsCursor.previousWindowIndex = ui->stackedWidget->currentIndex();
    this->windowsCursor.currentWindowIndex = 4;
 ui->stackedWidget->setCurrentIndex(4);
}
void MainWindow:: on_refresh_retriv_clicked(){
    ui->wait_label2->setHidden(false);
    this->on_loginButton_clicked();
    ui->wait_label2->setHidden(true);
}
void MainWindow::on_loginButton_clicked(){
    ui->wait_label->setHidden(false);
    ui->loginButton->setEnabled(false);
    try{
        this->checkForInternet();
        auth.getAuthObject()->grant();
    }catch(exceptionError & e){
        this->windowsCursor.previousWindowIndex = ui->stackedWidget->currentIndex();
        this->windowsCursor.currentWindowIndex = 2;
        ui->stackedWidget->setCurrentIndex(2);
        QMessageBox::critical(nullptr, QObject::tr("Error"),
        QObject::tr(e.getErrorMsg()), QMessageBox::Ok);
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
    ui->refresh_button->setHidden(true);
    ui->stop_button->setHidden(false);
    ui->search_button->setDisabled(true);
    try{
        int d,m,y;
        vector <Track> t = dbapi->retriveFromDB(ui->dateName->text()+".mu");
        sscanf(ui->dateName->text().toStdString().c_str(),"%d-%d-%d", &d,&m,&y);
        ui->date_ind->setText("These are the songs for: " + this->convertDateToQString(d,m,y));
        this->addToList(t);
    }catch(QString s){
        ui->refresh_button->setHidden(false);
        ui->stop_button->setHidden(true);
        //this is memory enhancment: we clear the old widget pointers to avoid memory leaks
        if(this->widitem.size() > 0){
            for (int i=0; i<=this->widitem.size()-1; i++) {
               delete widitem[i];
            }
        }
        this->widitem.clear();
        ui->listWidget->clear();
        ui->countText->setText("No Tracks for " + ui->dateName->text());
    }
}

void MainWindow::on_nav_clicked(){
    if(ui->calendarWidget->isHidden() == true){
        ui->calendarWidget->setHidden(false);
        //color calendar
        this->setCalendarMarks();

        ui->countText->setText("Note: yellow dates mean a play history is found");
    }else{
        ui->calendarWidget->setHidden(true);
        ui->countText->setText("-");
    }
}
void MainWindow::on_today_clicked(){
    //get date and time of sys to name the file after it (if file doesnt exist)
    QDateTime UTC(QDateTime::currentDateTimeUtc());
    QDateTime local = QDateTime(UTC.date(), UTC.time(), Qt::UTC).toLocalTime();
    int y,m,d;
    local.date().getDate( &y, &m, &d);
    QString h = QString::number(d) + "-" +QString::number(m) + "-" + QString::number(y);
    ui->dateName->setText(h);
    on_confirm_clicked();
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

