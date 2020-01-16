#include "user.h"
#include <QJsonArray>

User::User(const QJsonObject & data){
   id = data.value("id").toString();
   name = data.value("display_name").toString();
   QJsonArray array = data.value("images").toArray();
   imageRef = array.at(0).toObject().value("url").toString();
}
User :: ~User(){

}
