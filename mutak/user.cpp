#include "user.h"
#include <QJsonArray>
#include <QString>

User::User(const QJsonObject & data, QString t){
   id = data.value("id").toString();
   name = data.value("display_name").toString();
   QJsonArray array = data.value("images").toArray();
   imageRef = array.at(0).toObject().value("url").toString();
   token = t;
}
void User::printOnUI(Ui_MainWindow *mw){
    mw->disp_name->setText(name);
    mw->photo->setText(imageRef);
}
User :: ~User(){

}
