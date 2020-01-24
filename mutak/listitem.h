#ifndef LISTITEM_H
#define LISTITEM_H
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>

class listItem{
    QHBoxLayout hor;
    QVBoxLayout ver;
    QLabel photo;
    QLabel name;
    QLabel artist;
    QLabel duration;
    QLabel played;
public:
    listItem(QString photo, QString name, QString artist,
             QString duration, QString played);
};

#endif // LISTITEM_H
