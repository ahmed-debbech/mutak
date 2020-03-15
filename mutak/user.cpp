#include "user.h"
#include <QJsonArray>
#include <QString>
#include <QPixmap>
#include <iostream>
#include <QBrush>
#include <QPainter>
#include <QBitmap>
#include <iostream>

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
    mw->nameSettings->setText(name);
    mw->photo->setPixmap(QPixmap("://resources/unloaded-profile.png"));
    //load photo
    //we run a thread that retrives the image
    retrivePhotosThread rpt(imageRef);
    rpt.start();
    QPixmap pix;
    pix.loadFromData(rpt.downloadedData());
    pix = pix.scaled(64,64,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    mw->photo->setPixmap(pix);
}
User :: ~User(){

}
