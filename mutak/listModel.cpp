#include "listModel.h"
#include <QIcon>

listModel::listModel(vector <Track> tracks, QObject * parent = NULL)
    :QAbstractListModel(parent){
    v = tracks;
    /*QIcon icon;
    icon.addPixmap(p);
    QListWidgetItem::setIcon(icon);*/
}

