#include "user.h"
#include <QJsonArray>
#include <QString>
#include <QPixmap>
#include <iostream>
#include <QBrush>
#include <QPainter>
#include <QBitmap>

User::User(const QJsonObject & data, QString t, QString r){
   id = data.value("id").toString();
   name = data.value("display_name").toString();
   QJsonArray array = data.value("images").toArray();
   imageRef = array.at(0).toObject().value("url").toString();
   token = t;
   refToken = r;
}
void User::printOnUI(Ui_MainWindow *mw){
    mw->disp_name->setText(name);

    //load photo
    //we run a thread that retrives the image
    retrivePhotosThread rpt(imageRef);
    rpt.run(mw->photo);
}
User :: ~User(){

}
