/*
    Copyright (c) 2020 Ahmed Debbech

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
 */
#include "databaseapi.h"
#include <iostream>
#include <QMessageBox>
#include <QDateTime>
#include <QByteArray>
#include <QTextStream>
#include <QString>
#include <QDateTime>

/** 
 * Constructor for DatabaseAPI class
*/
DatabaseAPI::DatabaseAPI(){

}
/**
 * Creates and initializes the user set of directories to store the user data.
 * 
 * It creates the folders in the AppDataLocation standard path for Windows and checks them if they already exist
 * more specifically, It creates a folder with the user ID from spotify then it creates a folder called "db" which 
 * will later store the database files under ".mu" files.
 * The data base lives under: C:\Users\{user}}\AppData\Roaming\mutak\{spotifyUserID}\db
 * This methode must be called before prepareUserFiles().
 * @param QString id : the id of the user that will be used to create the directories
*/
void DatabaseAPI :: prepareUserDir(QString id){
    QStringList locations = QStandardPaths::standardLocations(QStandardPaths::AppDataLocation);
    userDir.setPath(locations[0]);
    if(userDir.exists() == true){
        if(userDir.cd(id)== false){
            userDir.mkdir(id);
        }
        userDir.cd(id);
        //create the settings file
        settingsDir = userDir.path()+"/config.set";
        QFile userSettingsFile;
        userSettingsFile.setFileName(settingsDir);
        if(userSettingsFile.exists() == false){
            if (userSettingsFile.open(QIODevice::WriteOnly | QIODevice::Text)){
                //file created
            }else{
                QMessageBox::critical(nullptr, QObject::tr("Error"),
                QObject::tr("Something went wrong in the database while preparing files!\n Please restart the application."), QMessageBox::Ok);
            }
        }
        userFiles.close();
        if(userDir.cd("db") == false){
            userDir.mkdir("db");
        }
        userDir.cd("db");
        userDirName = userDir.path() + "/";
    }else{
        userDir.setPath(locations[0]);
        userDir.cdUp();
        userDir.mkdir("mutak");
        prepareUserDir(id);
    }
}
/**
 * Creates and initializes the user set of files in the directories which are already created by prepareUserDir()
 * 
 * It creates and initializes the .mu file of the day which is located under {id}/db/dd-mm-yyyy.mu and it adds
 * the "user:{ID}" tag to the very beginning of the file.
 * This method must be called after prepareUserDir() is called.
 * @param QString userID : the user id that is needed to create the files
*/
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
            QObject::tr("Something went wrong in the database while preparing files!\n Please restart the application."), QMessageBox::Ok);
        }
    }
    userFiles.close();
}
/**
 * This is the main function that is called to send data to database and store it.
 * 
 * It get the array of tracks, it compares the timestamp of each one if the play date is as today 
 * it calls writeToFile() implicitly to write the track on the file, else if the play date is of yesterday
 * it calls writeToOldDayFile() implicitly to write the track on that files.
 * @param vector <Track> &t : an array full of track objects data to store it in database
 * @return it returns True if everything went file else False
 */
bool DatabaseAPI :: sendToDB(vector <Track> &t){

    userFiles.setFileName(filePathToday);
        for(unsigned int i=t.size(); i>0; i--){
            //check if the timestamp of the track is still the same day
            QDateTime UTC(QDateTime::currentDateTimeUtc());
            QDateTime local = QDateTime(UTC.date(), UTC.time(), Qt::UTC).toLocalTime();

            QDateTime playtimeConverted = QDateTime::fromString(t[i-1].getPlayDate().toString());
            if(playtimeConverted.date() == local.date()){
                if(checkForExistance(t[i-1]) == false){
                    try{
                        writeToFile(t[i-1]);
                    }catch(int i){
                        return false;
                    }
                }
            }else{
                if(playtimeConverted.date() < local.date()){
                    QString pastday = QString::number(playtimeConverted.date().day()) + "-" +
                            QString::number(playtimeConverted.date().month()) + "-"
                            + QString::number(playtimeConverted.date().year()) + ".mu";
                    try{
                        this->writeToOldDayFile(pastday, t[i-1]);
                    }catch(int i){
                        return false;
                    }
                }
            }
        }
        return true;
}
/**
 * This method is used only when storing a track that is not in the same day as today"
 * 
 * exp today is: 06-07-2020 and the date of play date of a given track is 05-06-2020 then the track will be 
 * stored in the files 05-07-2020.mu.
 * @param QString day : the day (name of file.mu) where the song will be stored
 * @param Track &t : the track oject that will be stored
 * this function is called implicitly by sendToDB()
*/
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
            QObject::tr("Something went wrong in database while writing!\n Please restart the application."), QMessageBox::Ok);
            throw 1;
            found = false;
        }
    }
    pastFile.close();

    //if not found
    if(found == false){
        if(pastFile.open(QIODevice::Append | QIODevice::Text)){
            QTextStream tofile(&pastFile);
            tofile << t.getName() << "|" << t.getArtist() << "|" << t.getDuration() << "|" << t.getPlayDate().toString() << "%" << t.getID() << "\n";
        }else{
            QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("Something went wrong in database while writing!\n Please restart the application."), QMessageBox::Ok);
        }
        pastFile.close();
    }
}
/** 
 * This is the main function that retreives data from database of a specefic day.
 * 
 * This method gets a date, first checks if the files of that date exists 
 * if not then there are no tracks for that day else it opens the file .mu and retrieves all the data
 * This function is overloaded.
 * @param QString : the date in format (dd-mm-yyyy) which is the same as the file name (dd-mm-yyyy.mu)
 * @return returns std::vector<Track> full of all the tracks in the file
 * @throw it throws QString if there are no tracks (file doesn't exist) or the files does exist but it is empty
 * @throw it throws also an constant number "1" if an error is encountred while retreiving data from DB
*/
vector <Track> DatabaseAPI :: retriveFromDB(QString f){
    vector<Track> t;
    QString ff = userDirName + f;
   QFile file(ff);
    if(file.exists() == false){
        throw QString("No Tracks found for this day.");
    }else{
        if(file.open(QIODevice::ReadOnly | QIODevice::Text) == true){
           t = readFromFile(&file);
           if(t.size() < 1){
            throw QString("No Tracks found for this day.");
           }
        }else{
            QMessageBox::critical(nullptr, QObject::tr("Error"),
            QObject::tr("Something went wrong in database while retriving data!\n Please restart the application."), QMessageBox::Ok);
            throw 1;
        }
        userFiles.close();
    }
    return t;
}
/**
 * This is the main overloaded function that retreives data from database of today
 * 
 * This method use the private class attribute which is the current user file object that points
 * to the file .mu of today. It works as the other retriveFromDB() function.
 * @return returns std::vector<Track> full of all the tracks in the file
 * @throw it throws QString if the file is empty
 * @throw it throws also an constant number "1" if an error is encountred while retreiving data from DB
 * @overload
*/
vector<Track> DatabaseAPI :: retriveFromDB(){
    vector<Track> t;
    if(userFiles.open(QIODevice::ReadOnly | QIODevice::Text)){
        t = readFromFile(&userFiles);
        if(t.size() < 1){
         throw QString("No Tracks found for this day.");
        }
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Error"),
        QObject::tr("Something went wrong in database while retriving data!\n Please restart the application."), QMessageBox::Ok);
        throw 1;
    }
    return t;
}
//====================== MISC ======================================
/**
 * @brief DatabaseAPI::checkFileExistance checks if a files exists
 * @param char * : the name of the file specified
 * @return bool : yes or no
 */
bool DatabaseAPI :: checkFileExistance(char *a){
    QString ff = userDirName + a;
   QFile file(ff);
    if(file.exists() == true){
        if(file.open(QIODevice::ReadOnly | QIODevice::Text) == true){
            userFiles.close();
            return true;
        }
    }
    return false;
}

//=====================PRV METHODES ============================
/**
 * This function is used as a core function of retriveFroDB() that reads structurally the content of the file.
 * 
 * It reads the data technically and structuraly as the rules set by the original author and it sends back the array full of data 
 * to the caller function.
 * It reads first the ID tag of the user at very beggining of the file, then it loops each line to fill a track object 
 * and push it to the vector. Note that each line in the file represents a track entry in database.
 * @param QFile * : a pointer to the file to read from.
 * @return returns a vector<Track> full of tracks read from the file.
*/
vector <Track> DatabaseAPI :: readFromFile(QFile * userFiles){
    vector<Track> t;
    while(!userFiles->atEnd()){
        QByteArray arr;
        do{
            arr = userFiles->readLine();
        }while(arr.contains("user:") == true);
            if(userFiles->atEnd()){
                break;
            }
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
           QDateTime datePlay;
           datePlay = QDateTime::fromString(play);
           Track tr(name,artist,dur.toDouble(),datePlay,id);
           t.push_back(tr);
    }
    userFiles->close();
    return t;
}
/**
 * This function is used as a core function of sendToDB() that writes structurally the content of the file.
 * 
 * It writes the data technically and structuraly as the rules set by the original author.
 * It writes one track at each call. and it opens the file in Append mode.
 * format of the line: songname|artistname|duration|playdate%trackURI
 * @param Track & : representing the track to be appended to the file
 * @throw it throws contant number "1" if the operation failed.
*/
void DatabaseAPI :: writeToFile(Track & t){
    if(userFiles.open(QIODevice::Append | QIODevice::Text)){
        QTextStream tofile(&userFiles);
        tofile << t.getName() << "|" << t.getArtist() << "|" << t.getDuration() << "|" << t.getPlayDate().toString() << "%" << t.getID() << "\n";
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Error"),
        QObject::tr("Something went wrong in database while writing!\n Please restart the application."), QMessageBox::Ok);
        throw 1;
    }
    userFiles.close();
}
/**
 * This function checks if a track passed in parametre exists at the current day.
 * 
 * it gets the files object that points to the "today" file and loops over it linearly.
 * If the file of today doesn't exist yet it creates it also and it returns false = not found.
 * @param Track & : representing the track to be looking for.
 * @return it returns bool = true if found else false.
*/
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
            QObject::tr("Something went wrong in database while creating files! Please restart the application."), QMessageBox::Ok);
            found = false;
        }
    }
    userFiles.close();
    return found;
}
