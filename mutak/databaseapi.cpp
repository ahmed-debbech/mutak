#include "databaseapi.h"
#include <iostream>

DatabaseAPI::DatabaseAPI(){

}
void DatabaseAPI :: prepareUserDir(QString id){
    QString ss(QStandardPaths::AppDataLocation);
    userDir.setPath(ss);
}
