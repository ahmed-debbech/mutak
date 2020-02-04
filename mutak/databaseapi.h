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
    QString filePathToday;
    QString userDirName;
public:
    DatabaseAPI();
    void prepareUserDir(QString id);
    void prepareUserFiles(QString userID);
    void sendToDB(vector <Track> & t);
    vector<Track> retriveFromDB();
    void writeToOldDayFile(QString day, Track & t);
private:
    void writeToFile( Track & t);
    bool checkForExistance(Track & t);
};

#endif // DATABASEAPI_H
