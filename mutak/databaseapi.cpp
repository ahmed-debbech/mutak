#include "databaseapi.h"
#include <iostream>

DatabaseAPI::DatabaseAPI(){

}
void DatabaseAPI :: prepareUserDir(QString id){
    QString s = QStandardPaths::locate(QStandardPaths::AppDataLocation,
                                       QString(), QStandardPaths::LocateDirectory);
    userDir.setPath(s);
    if(userDir.exists() == true){
        if(userDir.cd(id)== false){
            userDir.mkdir(id);
        }
    }
}
