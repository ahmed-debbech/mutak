#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authorizer.h"
#include <QDesktopServices>
#include <iostream>
#include <QOAuth2AuthorizationCodeFlow>

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
    auth.getAuthObject()->grant();
}


void MainWindow:: isGranted(){

    if(auth.getAuthObject()->status() == QAbstractOAuth::Status::Granted){
        ui->plainTextEdit->appendPlainText("Signal granted received");
        Token = auth.getAuthObject()->token();
        ui->plainTextEdit->appendPlainText(Token);
    }else{
        std::cout << "Could not connect" << std::endl;
    }
}

