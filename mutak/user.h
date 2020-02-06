#ifndef USER_H
#define USER_H

#include <QString>
#include <QJsonObject>
#include "ui_mainwindow.h"
#include <QObject>
#include "retrivephotosthread.h"

using namespace std;

class User : public QObject{
    QString id;
    QString name;
    QString imageRef;
    QString token;
    QString refToken;
    QByteArray photo;
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
