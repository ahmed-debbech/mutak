#ifndef LISTITEM_H
#define LISTITEM_H
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include "track.h"
#include <QMetaType>


class listItem{
    QHBoxLayout *main_layout;
     QVBoxLayout *m_ver1;
     QVBoxLayout* m_ver2;
     QLabel *m_photo;
     QLabel *m_name;
     QLabel *m_artist;
     QLabel *m_duration;
     QLabel *m_played;
     QWidget *m_item;
 public:
     listItem(Track & v);
     listItem() = default;
     listItem(const listItem &) = default;
     QWidget *getItem(){return m_item;}
     ~listItem();
 };

 #endif // LISTITEM_H
