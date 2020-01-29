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
        for(unsigned int i=0; i<=49; i++){
            if(checkForExistance(t[i]) == false){
                writeToFile(t[i]);
            }
        }
}
//=====================PRV METHODES ============================
void DatabaseAPI :: writeToFile(Track & t){
    if(userFiles.open(QIODevice::Append | QIODevice::Text)){
        QTextStream tofile(&userFiles);
        tofile << t.getName() << "|" << t.getArtist() << "|" << t.getDuration() << "|" << t.getPlayDate() << "|" << t.getID() << "\n";
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Error"),
        QObject::tr("Something went wrong! Please restart the application."), QMessageBox::Ok);
    }
    userFiles.close();
}
bool DatabaseAPI :: checkForExistance(Track & t){
    bool found = false;
    if(userFiles.open(QIODevice::ReadOnly | QIODevice::Text)){
        while((!userFiles.atEnd()) && (found == false)){
            QByteArray arr = userFiles.readLine();
            int j =0;
            do{
               j++;
            }while(arr[j] != '|');
            j++;
            QString id;
            for(int k=0; arr[k]!='\n'; k++){
                id += arr[k];
            }
            std::cout << "id of line extracted from file " << id.toStdString() <<std::endl;
            if(t.getID() == id){
                found = true;
            }
        }
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Error"),
        QObject::tr("Something went wrong! Please restart the application."), QMessageBox::Ok);
    }
    userFiles.close();
    return found;
}
