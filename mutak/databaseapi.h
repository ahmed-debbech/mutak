#ifndef DATABASEAPI_H
#define DATABASEAPI_H

#include <QFile>
#include <QDir>
#include <QString>
#include <QStandardPaths>

class DatabaseAPI{
    QDir userDir;
public:
    DatabaseAPI();
    void prepareUserDir(QString id);
};

#endif // DATABASEAPI_H
