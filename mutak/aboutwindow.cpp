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
#include <QtNetwork>
#include <QWidget>

#include "ui_mainwindow.h"
#include "mainwindow.h"

/**
 * This methode is used when go back button in about section is clicked.
*/
void MainWindow :: on_gobackAbout_clicked(){
       ui->stackedWidget->setCurrentIndex(this->windowsCursor.previousWindowIndex);
       this->windowsCursor.currentWindowIndex = this->windowsCursor.previousWindowIndex;
}
/**
 * This method is used when twitter social button is pressed.
*/
void MainWindow::on_twitter_clicked(){
     QDesktopServices::openUrl(QUrl("https://twitter.com/AhmedDebb", QUrl::TolerantMode));
}
/**
 * This method is used when linkedin button is pressed.
*/
void MainWindow::on_linkedin_clicked(){
    QDesktopServices::openUrl(QUrl("https://www.linkedin.com/in/ahmed-debbech-90b834179/", QUrl::TolerantMode));
}
/**
 * This method is used when github social button is pressed
*/
void MainWindow::on_github_clicked(){
     QDesktopServices::openUrl(QUrl("https://github.com/ahmed-debbech/mutak", QUrl::TolerantMode));
}
/**
 * This method is used when website button is pressed.
*/
void MainWindow :: on_website_clicked(){
    QDesktopServices::openUrl(QUrl("http://www.mutak.site/", QUrl::TolerantMode));
}
