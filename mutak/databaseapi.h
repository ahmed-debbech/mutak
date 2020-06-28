#ifndef DATABASEAPI_H
#define DATABASEAPI_H

#include <QFile>
#include <QDir>
#include <QString>
#include <QStandardPaths>
#include <vector>
#include "track.h"
#include "track.h"

using namespace std;
class DatabaseAPI{
    QDir userDir;
    QFile userFiles;
    QString settingsDir;
    QString filePathToday;
    QString userDirName;
public:
    //getters and setters
    QDir getUserDir(){return userDir;}
    QString getUserSettingsPath(){return settingsDir;}
    //initialization of folders and files depending in user id
    DatabaseAPI();
    void prepareUserDir(QString id);
    void prepareUserFiles(QString userID);

    //input/output from DB,it uses the private methodes below
    bool sendToDB(vector <Track> & t);
    vector<Track> retriveFromDB();
    vector<Track> retriveFromDB(QString fileName);
 private:
    vector <Track> readFromFile(QFile * userFiles);
    void writeToOldDayFile(QString day, Track & t); // this private method is needed when it is necessary to write to past day files.
    void writeToFile( Track & t);
    bool checkForExistance(Track & t);
};

#endif // DATABASEAPI_H
