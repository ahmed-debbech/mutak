#ifndef LISTITEM_H
#define LISTITEM_H
#include <QListWidgetItem>
#include <QLabel>
#include <QString>
#include <QPixmap>
#include <QVariant>

class listItem : public QListWidgetItem{
    QLabel photo;
    QLabel name;
    QLabel artist;
    QLabel playedAt;
public:
    listItem(QPixmap&, QString&, QString&, QString&);
    virtual void setData(int role, const QVariant & value);
};

#endif // LISTITEM_H
