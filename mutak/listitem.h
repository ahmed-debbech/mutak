#ifndef LISTITEM_H
#define LISTITEM_H
#include <QListWidgetItem>
#include <QLabel>
#include <QString>
#include <QPixmap>

class listItem : public QListWidgetItem{
    QLabel photo;
    QLabel name;
    QLabel artist;
    QLabel playedAt;
public:
    listItem(QPixmap&, QString&, QString&, QString&);
};

#endif // LISTITEM_H
