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
#include "authorizer.h"
#include <iostream>
#include <QOAuthHttpServerReplyHandler>
#include <QDesktopServices>
#include <QObject>
#include "api_keys.h"
/**
 * This is the constructor of the Authorizer class and it initializes the client ID and client secret attributes.
 */
Authorizer::Authorizer(){
    clientID = ID;
    clientSecret = SECRET;
}
/**
 * This method is part of Authorizer class, it sets the values for the QOAuth2AuthorizationCodeFlow object attribute
 * before starting the connection of authorization
*/
void Authorizer :: setValues(){
    auto replyHandler = new QOAuthHttpServerReplyHandler(80, this);
    replyHandler->setCallbackPath("cb");
    spotify.setReplyHandler(replyHandler);
    spotify.setAuthorizationUrl(QUrl("https://accounts.spotify.com/authorize"));
    spotify.setAccessTokenUrl(QUrl("https://accounts.spotify.com/api/token"));
    spotify.setClientIdentifier(clientID);
    spotify.setClientIdentifierSharedKey(clientSecret);
    spotify.setScope("user-read-private user-read-recently-played playlist-read-private playlist-read-collaborative");
}
/**
 * This method is part of Authorizer class, it sets the values for the QOAuth2AuthorizationCodeFlow object attribute
 * before starting the connection of authorization by setting the token manually from windows Credential manager.
 * This is an overloaded method.
 * @param QString token: the access token to be set.
 * @param QString ref: the refresh token
*/
void Authorizer :: setValues(QString token, QString ref){
    auto replyHandler = new QOAuthHttpServerReplyHandler(80, this);
    replyHandler->setCallbackPath("cb");
    spotify.setReplyHandler(replyHandler);
    spotify.setAuthorizationUrl(QUrl("https://accounts.spotify.com/authorize"));
    spotify.setAccessTokenUrl(QUrl("https://accounts.spotify.com/api/token"));
    spotify.setToken(token);
    spotify.setRefreshToken(ref);
    spotify.setClientIdentifier(clientID);
    spotify.setClientIdentifierSharedKey(clientSecret);
    spotify.setScope("user-read-private user-read-recently-played");
}
/**
 * This method belongs to Authorizer class, after setting the values this function is called after that.
 * It opens the default browser to complete the authorization
*/ 
void Authorizer :: connectToBrowser(){
    connect(&spotify, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser,
             &QDesktopServices::openUrl);
}
/**
 * This method belongs to Authoriizer class, it behaves as a getter which returns a pointer of the 
 * basic authorization object of QT QOAuth2AuthorizationCodeFlow.
 * @return a pointer on the object QOAuth2AuthorizationCodeFlow that makes the authorization process.
*/
QOAuth2AuthorizationCodeFlow * Authorizer :: getAuthObject(){
    return &spotify;
}
QJsonObject Authorizer:: getFromEndPoint(Authorizer& auth, const QUrl &q, User *user){
    QJsonObject root;
    QEventLoop loop; // to never quit the function untill the reply is finished
    QTimer timer;    // timer for time out when no response
    timer.setSingleShot(true);
    auto reply = auth.getAuthObject()->get(q);
    connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
    connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));

    connect(reply, &QNetworkReply::finished, [&root, reply]() { //this is a lambda fun
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
