#ifndef DATABASEAPI_H
#define DATABASEAPI_H

#include <QFile>
#include <QDir>
#include <QString>
#include <QStandardPaths>
#include <vector>
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
    void prepareUserFiles();
    void sendToDB(vector <Track> & t);
private:
    void f();
};

#endif // DATABASEAPI_H
