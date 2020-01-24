#ifndef LISTITEM_H
#define LISTITEM_H
#include <QAbstractListModel>
#include <QLabel>
#include <QString>
#include <QPixmap>
#include <QVariant>
#include "track.h"
#include <vector>
#include <QList>
#include "listitem.h"

using namespace std;
class listModel : public QAbstractListModel{
   mutable vector <Track> v;
public:
    listModel(vector <Track>& tracks, QObject * parent);
    QVariant data(const QModelIndex &index, int role) const ;
     QVariant headerData(int section, Qt::Orientation orientation,
                         int role = Qt::DisplayRole) const;
     int rowCount(const QModelIndex &parent = QModelIndex())const;

};

#endif // LISTITEM_H
