#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QString>
#include <vector>
#include "track.h"
#include <iostream>

using namespace std;

class Playlist{
        QString id;
        QString name;
        QString description;
        QString ownerId;
        vector<Track> tracks;
public:
    Playlist(QString id, QString name, QString description, QString ownedId, vector<Track>);
    QString getId() const;
    void setId(const QString &value);
    QString getName() const;
    void setName(const QString &value);
    QString getDescription() const;
    void setDescription(const QString &value);
    QString getOwnerId() const;
    void setOwnerId(const QString &value);
    vector<Track> getTracks() const;
    void setTracks(const vector<Track> &value);
};

#endif // PLAYLIST_H
