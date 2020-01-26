#include "databaseapi.h"
#include <iostream>

DatabaseAPI::DatabaseAPI(){

}
void DatabaseAPI :: prepareUserDir(QString id){
    QString ss(QStandardPaths::AppDataLocation);
    userDir.setPath(ss);
    if(userDir.exists() == true){
        std::cout << "flder exists" << std::endl;
    }
}
