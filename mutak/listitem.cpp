#include "listitem.h"

listItem::listItem(QPixmap &p, QString& n, QString& a, QString& pla){
    photo.setPixmap(p);
    name.setText(n);
    artist.setText(a);
    playedAt.setText(pla);
}
