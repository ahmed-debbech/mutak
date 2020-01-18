#include "user.h"
#include <QJsonArray>
#include <QString>
#include "photodownloader.h"
#include <QPixmap>
#include <iostream>

User::User(const QJsonObject & data, QString t){
   id = data.value("id").toString();
   name = data.value("display_name").toString();
   QJsonArray array = data.value("images").toArray();
   imageRef = array.at(0).toObject().value("url").toString();
   token = t;
   photoDownloader pd(imageRef, NULL);
   photo = pd.downloadedData();
   std::cout<< photo.toStdString() << std::endl;
}
void User::printOnUI(Ui_MainWindow *mw){
    mw->disp_name->setText(name);
    mw->photo->setText(imageRef);
    QPixmap p;
    p.loadFromData(photo);
    std::cout << p.height() << std::endl;
    mw->photo->setPixmap(p);
}
User :: ~User(){

}
