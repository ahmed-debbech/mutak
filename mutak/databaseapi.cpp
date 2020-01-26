#include "databaseapi.h"
#include <iostream>
#include <QMessageBox>
#include <QDateTime>

DatabaseAPI::DatabaseAPI(){

}
void DatabaseAPI :: prepareUserDir(QString id){
    QString s = QStandardPaths::locate(QStandardPaths::AppDataLocation,
                                       QString(), QStandardPaths::LocateDirectory);
    userDir.setPath(s);
    if(userDir.exists() == true){
        if(userDir.cd(id)== false){
            userDir.mkdir(id);
            userDir.cd(id);
        }
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Error"),
        QObject::tr("Could not find the correct directory of Mutak"), QMessageBox::Ok);
    }
}
void DatabaseAPI :: prepareUserFiles(){
    //get date and time of sys to name the file after it (if file doesnt exist)
    QDateTime UTC(QDateTime::currentDateTimeUtc());
    QDateTime local(UTC.toLocalTime());
    int y,m,d;
    local.date().getDate( &y, &m, &d);

    userFiles.setFileName(userDir.path() +"/"+ QString::number(d) + "-" +
                          QString::number(m) + "-" + QString::number(y) +  ".mu");
    std::cout << userFiles.fileName().toStdString() <<std::endl;
    if(userFiles.exists() == false){
        if (userFiles.open(QIODevice::WriteOnly | QIODevice::Text)){

        }else{

        }
    }
}
