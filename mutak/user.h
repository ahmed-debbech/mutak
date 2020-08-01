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
/**
 * @file user.h
 *
 * @brief Everything related to the user logged-in
 *
 * @author Ahmed Debbech
 *
 */
#ifndef USER_H
#define USER_H

#include <QString>
#include <QJsonObject>
#include "ui_mainwindow.h"
#include <QObject>
#include "retrivephotosthread.h"

using namespace std;
/**
 * This class holdes all the data related to the user logged in 
 * 
 * It contains almost everything needed to login like access tokens, it inherits QObject.
*/
class User : public QObject{
    QString id; ///< used ID for Spotify
    QString name; ///< user name for Spotify
    QString imageRef; ///< user image link to download from 
    QString token; ///< access token 
    QString refToken; ///< refresh access token 
    QByteArray photo; ///< the data of the image after download
private slots:
    void delete_threads(retrivePhotosThread * i){delete i;}
public:
    User(const QJsonObject & data, QString token, QString ref);
    void setId(QString i){ id = i;}
    void setName(QString i){ name = i;}
    void setImageRef(QString i){ imageRef = i;}
    void setToken(QString t){ token= t;}
    QString getId(){ return id;}
    QString getName(){ return name;}
    QString getImageRef(){ return imageRef;}
    QString getToken(){ return token;}
    void printOnUI(Ui_MainWindow * mw);
    ~User();
};

#endif // USER_H
