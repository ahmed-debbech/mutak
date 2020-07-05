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
/**
 * @file databaseapi.h
 *
 * @brief Contains the whole API needed to access the local database from the app
 *
 * @author Ahmed Debbech
 *
 */
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
/**
 * This only class is used for every communication with the local database (send/retreive)
 * 
 * A full class and an only one for the database connections contains a powerful API. 
 * This class is instantiated each time the usr logs in.
*/
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
