#include "listitem.h"

listItem::listItem(QPixmap &p, QString& n, QString& a, QString& pla)
    :QListWidgetItem(n){
    photo.setPixmap(p);
    name.setText(n);
    artist.setText(a);
    playedAt.setText(pla);
    //QListWidgetItem::setText("hee");
}
void listItem :: setData(int role , const QVariant &value){
    role = 0;

}

