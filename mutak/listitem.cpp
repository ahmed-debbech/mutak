#include "listitem.h"
#include <QIcon>

listItem::listItem(QPixmap &p, QString& n, QString& a, QString& pla)
    :QListWidgetItem(a + " - " +n){
    photo.setPixmap(p);
    name.setText(n);
    artist.setText(a);
    playedAt.setText(pla);
    QIcon icon;
    icon.addPixmap(p);
    QListWidgetItem::setIcon(icon);
}
void listItem :: setData(int role , const QVariant &value){
    role = 2;

}

