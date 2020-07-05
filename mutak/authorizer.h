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
 * @file authorizer.h
 *
 * @brief This file is for everything about authorisation workflow
 *
 * @author Ahmed Debbech
 *
 */
#ifndef AUTHORIZER_H
#define AUTHORIZER_H

#include <QOAuthHttpServerReplyHandler>
#include <QOAuth2AuthorizationCodeFlow>
#include <QString>
#include <QMainWindow>

/**
 * This class contains everything needed to authorize a user in OAuth2 workflow.
 * 
 * This class inhertis QObject to make it QT-like classes and it has the keys needed to start an authorization process with 
 * the server.
 * This Class should be instantiated each time a user logs in.
*/
class Authorizer : public QObject{
    QOAuth2AuthorizationCodeFlow spotify; //the flow of the authorization
    QString clientID;
    QString clientSecret;
public:
    Authorizer();
    void setValues();
    void connectToBrowser();
    QOAuth2AuthorizationCodeFlow * getAuthObject();
};

#endif // AUTHORIZER_H
