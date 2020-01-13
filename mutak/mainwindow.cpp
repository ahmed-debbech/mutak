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
   auth.setValues();
   auth.openBrowser();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_loginButton_clicked()
{
    auth.getAuthObject()->grant();
}


