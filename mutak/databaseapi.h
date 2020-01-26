#ifndef DATABASEAPI_H
#define DATABASEAPI_H

#include <QFile>
#include <QDir>
#include <QString>
#include <QStandardPaths>

class DatabaseAPI{
    QDir userDir;
    QFile userFiles;
    QString filePathToday;
    QString userDirName;
public:
    DatabaseAPI();
    void prepareUserDir(QString id);
    void prepareUserFiles();
};

#endif // DATABASEAPI_H
