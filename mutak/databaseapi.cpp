#include "databaseapi.h"
#include <iostream>

DatabaseAPI::DatabaseAPI(){

}
void DatabaseAPI :: prepareUserDir(QString id){
    QString ss(QStandardPaths::DesktopLocation);
    std::cout << ss.toStdString() << std::endl;

    userDir.setPath(ss);
    if(userDir.exists() == true){
        std::cout << ss.toStdString() << std::endl;
    }
}
