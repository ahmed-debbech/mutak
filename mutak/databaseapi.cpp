#include "databaseapi.h"
#include <iostream>
#include <QMessageBox>
#include <QDateTime>
#include <QByteArray>
#include <QTextStream>
#include <QString>
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
void DatabaseAPI :: prepareUserFiles(QString userID){
    //get date and time of sys to name the file after it (if file doesnt exist)
    QDateTime UTC(QDateTime::currentDateTimeUtc());
    QDateTime local = QDateTime(UTC.date(), UTC.time(), Qt::UTC).toLocalTime();
    int y,m,d;
    local.date().getDate( &y, &m, &d);

    userFiles.setFileName(userDirName + QString::number(d) + "-" +
                          QString::number(m) + "-" + QString::number(y) +  ".mu");
    filePathToday = userFiles.fileName();
    //creating file of that specefic day
    if(userFiles.exists() == false){
        if (userFiles.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream out(&userFiles);
            out << "user:" << userID <<"\n";
        }else{
            QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("Something went wrong in the database! Please restart the application."), QMessageBox::Ok);
        }
    }
    userFiles.close();
}
void DatabaseAPI :: sendToDB(vector <Track> &t){

    userFiles.setFileName(filePathToday);
        for(unsigned int i=t.size(); i>0; i--){
            //check if the timestamp of the track is still the same day
            QDateTime UTC(QDateTime::currentDateTimeUtc());
            QDateTime local = QDateTime(UTC.date(), UTC.time(), Qt::UTC).toLocalTime();

            QDateTime playtimeConverted = QDateTime::fromString(t[i-1].getPlayDate());
            if(playtimeConverted.date() == local.date()){
                if(checkForExistance(t[i-1]) == false){
                    writeToFile(t[i-1]);
                }
            }else{
                if(playtimeConverted.date() < local.date()){
                    QString pastday = QString::number(playtimeConverted.date().day()) + "-" +
                            QString::number(playtimeConverted.date().month()) + "-"
                            + QString::number(playtimeConverted.date().year()) + ".mu";
                    this->writeToOldDayFile(pastday, t[i-1]);
                }
            }
        }
}
void DatabaseAPI :: writeToOldDayFile(QString day, Track & t){
    QFile pastFile;
    pastFile.setFileName(userDirName + day);
    bool found = false;

    //check for existance
    if(pastFile.open(QIODevice::ReadOnly | QIODevice::Text)){
        while((!pastFile.atEnd()) && (found == false)){
            QByteArray arr = pastFile.readLine();
            int j =0;
            do{
               j++;
            }while(arr[j] != '%');
            j++;
            QString id;
            for(int k=j; arr[k]!='\n'; k++){
                id += arr[k];
            }
            if(t.getID() == id){
                found = true;
            }
        }
    }else{
        // if the file doesnt exist create it
        if(pastFile.open(QIODevice::WriteOnly | QIODevice::Text)){
            found = false;
        }else{
            QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("Something went wrong in database! Please restart the application."), QMessageBox::Ok);
            found = false;
        }
    }
    pastFile.close();

    //if not found
    if(found == false){
        if(pastFile.open(QIODevice::Append | QIODevice::Text)){
            QTextStream tofile(&pastFile);
            tofile << t.getName() << "|" << t.getArtist() << "|" << t.getDuration() << "|" << t.getPlayDate() << "%" << t.getID() << "\n";
        }else{
            QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("Something went wrong in database! Please restart the application."), QMessageBox::Ok);
        }
        pastFile.close();
    }
}
vector <Track> DatabaseAPI :: retriveFromDB(QString f){
    vector<Track> t;
    f = userDirName + f;
    QFile file(f);
    if(file.exists() == false){
        throw QString("No Tracks found for this day.");
    }else{
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
            while(!file.atEnd()){
                QByteArray arr;
                do{
                    arr = userFiles.readLine();
                }while(arr.contains("user:") == true);
                   int y=0;
                   QString name,artist,dur,play,id;
                   do{
                       name += arr[y];
                       y++;
                   }while(arr[y] != '|');
                   y++;
                   do{
                       artist += arr[y];
                       y++;
                   }while(arr[y] != '|');
                   y++;
                   do{
                       dur += arr[y];
                       y++;
                   }while(arr[y] != '|');
                   y++;
                   do{
                       play += arr[y];
                       y++;
                   }while(arr[y] != '%');
                   y++;
                   do{
                       id += arr[y];
                       y++;
                   }while(arr[y] != '\n');
                   Track tr(name,artist,dur.toDouble(),play,id);
                   t.push_back(tr);
            }
        }else{
            QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("Something went wrong in database! Please restart the application."), QMessageBox::Ok);
        }
        userFiles.close();
    }
    return t;
}
vector<Track> DatabaseAPI :: retriveFromDB(){
    vector<Track> t;
    if(userFiles.open(QIODevice::ReadOnly | QIODevice::Text)){
        while(!userFiles.atEnd()){
            QByteArray arr;
            do{
                arr = userFiles.readLine();
            }while(arr.contains("user:") == true);
               int y=0;
               QString name,artist,dur,play,id;
               do{
                   name += arr[y];
                   y++;
               }while(arr[y] != '|');
               y++;
               do{
                   artist += arr[y];
                   y++;
               }while(arr[y] != '|');
               y++;
               do{
                   dur += arr[y];
                   y++;
               }while(arr[y] != '|');
               y++;
               do{
                   play += arr[y];
                   y++;
               }while(arr[y] != '%');
               y++;
               do{
                   id += arr[y];
                   y++;
               }while(arr[y] != '\n');
               Track tr(name,artist,dur.toDouble(),play,id);
               t.push_back(tr);
        }
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Error"),
        QObject::tr("Something went wrong in database! Please restart the application."), QMessageBox::Ok);
    }
    userFiles.close();
    return t;
}
//=====================PRV METHODES ============================
void DatabaseAPI :: writeToFile(Track & t){
    if(userFiles.open(QIODevice::Append | QIODevice::Text)){
        QTextStream tofile(&userFiles);
        tofile << t.getName() << "|" << t.getArtist() << "|" << t.getDuration() << "|" << t.getPlayDate() << "%" << t.getID() << "\n";
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Error"),
        QObject::tr("Something went wrong in database! Please restart the application."), QMessageBox::Ok);
    }
    userFiles.close();
}
bool DatabaseAPI :: checkForExistance(Track & t){
    bool found = false;
    if(userFiles.open(QIODevice::ReadOnly | QIODevice::Text)){
        while((!userFiles.atEnd()) && (found == false)){
            QByteArray arr;
            do{
                arr = userFiles.readLine();
            }while(arr.contains("user:") == true);
            int j =0;
            do{
               j++;
            }while(arr[j] != '%');
            j++;
            QString id;
            for(int k=j; arr[k]!='\n'; k++){
                id += arr[k];
            }
            if(t.getID() == id){
                found = true;
            }
        }
    }else{
        // if the file doesnt exist create it
        if(userFiles.open(QIODevice::WriteOnly | QIODevice::Text)){
            found = false;
        }else{
            QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("Something went wrong in database! Please restart the application."), QMessageBox::Ok);
            found = false;
        }
    }
    userFiles.close();
    return found;
}
