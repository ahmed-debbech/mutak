#ifndef USER_H
#define USER_H

#include <QString>
#include <QJsonObject>

using namespace std;

class User{
    QString id;
    QString name;
    QString imageRef;
public:
    User(const QJsonObject & data);
    void setId(QString i){ id = i;}
    void setName(QString i){ name = i;}
    void setImageRef(QString i){ imageRef = i;}
    QString getId(){ return id;}
    QString getName(){ return name;}
    QString getImageRef(){ return imageRef;}
    ~User();
};

#endif // USER_H
