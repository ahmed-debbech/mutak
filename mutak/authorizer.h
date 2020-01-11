#ifndef AUTHORIZER_H
#define AUTHORIZER_H

#include <QOAuthHttpServerReplyHandler>
#include <QOAuth2AuthorizationCodeFlow>
#include <QString>
#include <QMainWindow>

class Authorizer : public QObject{
    QOAuth2AuthorizationCodeFlow spotify; //the flow of the authorization
    QString clientID;
    QString clientSecret;
public:
    Authorizer();
    void setValues(QMainWindow * w);
};

#endif // AUTHORIZER_H
