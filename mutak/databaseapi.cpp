#include "databaseapi.h"
#include <iostream>
#include <QMessageBox>
#include <QDateTime>
#include <QByteArray>
#include <QTextStream>

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
        userDir.cd(id);
        if(userDir.cd("db") == false){
            userDir.mkdir("db");
        }
        userDir.cd("db");
        userDirName = userDir.path() + "/";
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

    userFiles.setFileName(userDirName + QString::number(d) + "-" +
                          QString::number(m) + "-" + QString::number(y) +  ".mu");
    filePathToday = userFiles.fileName();
    if(userFiles.exists() == false){
        if (userFiles.open(QIODevice::WriteOnly | QIODevice::Text)){

        }else{
            QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("Something went wrong in the database! Please restart the application."), QMessageBox::Ok);
        }
    }
    userFiles.close();
}
void DatabaseAPI :: sendToDB(vector <Track> &t){
    userFiles.setFileName(filePathToday);
    bool found = false;
    if (userFiles.open(QIODevice::ReadWrite | QIODevice::Text)){
        for(unsigned int i=0; i<=49; i++){
            if(userFiles.atEnd() == true){
                QTextStream out(&userFiles);
                out << "The magic number is: " << 49 << "\n";
                found = true;
            }else{
                while((!userFiles.atEnd()) && (found == false)){
                    QByteArray arr = userFiles.readLine();
                    int j =0;
                    do{
                       j++;
                    }while(arr[j] != ':');
                    j++;
                    QString id;
                    for(int k=0; arr[k]!='\0'; k++){
                        id += arr[k];
                    }
                    std::cout << "id of line extracted from file" << id.toStdString() <<std::endl;
                    if(t[i].getLink() != id){
                        QTextStream out(&userFiles);
                        out << "The magic number is: " << 49 << "\n";
                        found = true;
                    }
                }
            }
        }
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Error"),
        QObject::tr("Something went wrong! Please restart the application."), QMessageBox::Ok);
    }
    userFiles.close();
}
