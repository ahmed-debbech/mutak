#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authorizer.h"
#include <QDesktopServices>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   // auto replyHandler = new QOAuthHttpServerReplyHandler(8080, this);
     //  spotify.setReplyHandler(replyHandler);
       spotify.setAuthorizationUrl(QUrl("https://accounts.spotify.com/authorize"));
       spotify.setAccessTokenUrl(QUrl("https://accounts.spotify.com/api/token"));
       spotify.setClientIdentifier("17003af1c95b4506b21dbf98110a6e6f");
       spotify.setClientIdentifierSharedKey("52291278398442e1961f84615d55a097");
       spotify.setScope("user-read-private");

       connect(&spotify, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser,
                &QDesktopServices::openUrl);
    std::cout << "hey" << std::endl;
   /* spotify.authorizeWithBrowser();
    QDesktopServices ds;
    QUrl u ("https://example.com");
    ds.openUrl(u);
       connect(&spotify, &QOAuth2AuthorizationCodeFlow::statusChanged,
               this, &MainWindow::authStatusChanged);

       connect(&spotify, &QOAuth2AuthorizationCodeFlow::granted,
               this, &MainWindow::granted); */
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    spotify.grant();
}

void MainWindow::granted ()
{
    ui->plainTextEdit->appendPlainText("Signal granted received");

    QString token = spotify.token();
    ui->plainTextEdit->appendPlainText("Token: " + token);
}

void MainWindow::authStatusChanged(QAbstractOAuth::Status status)
{
    QString s;
    if (status == QAbstractOAuth::Status::Granted)
        s = "granted";

    if (status == QAbstractOAuth::Status::TemporaryCredentialsReceived) {
        s = "temp credentials";
        //oauth2.refreshAccessToken();
    }

    ui->plainTextEdit->appendPlainText("Auth Status changed: " + s +  "\n");
}
