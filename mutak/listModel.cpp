#include "listModel.h"
#include <QIcon>
#include <QVariant>
#include <QString>
#include <QVector>

listModel::listModel(vector <Track> &tracks, QObject * parent = 0)
    :QAbstractListModel(parent){
    v = tracks;
    items.push_back(v[0]);
}
Track  getd(vector <Track> v){
    Track t(v[0].getName(), v[0].getArtist(), v[0].getDuration(), v[0].getPlayDate(), v[0].getLink());
    return t;
}
QVariant listModel::data(const QModelIndex &index, int role)const{
    if (!index.isValid()){
        return QVariant();
    }

    if (index.row() >= static_cast<int>(v.size())){
        return QVariant();
    }

    if (role == Qt::DisplayRole){
        return QVariant(QVariant::fromValue<listItem>(items[0]));
    }
     return QVariant();
}
QVariant listModel :: headerData(int section, Qt::Orientation orientation,int role) const{

}
int listModel :: rowCount(const QModelIndex &parent) const{
    return static_cast<int>(v.size());
}
