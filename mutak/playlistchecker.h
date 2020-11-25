#ifndef PLAYLISTCHECKER_H
#define PLAYLISTCHECKER_H

#include "QJsonObject"
#include "mainwindow.h"
#include "playlist.h"

class PlaylistChecker{
private:
    QJsonObject data;
    vector<Playlist> owned;
    User * user;
    Authorizer * auth;
    DatabaseAPI * db;
    vector<Track> newTracks;

    vector<Track> fetchTracks(QString, int);
    vector<Playlist> getOwnedPlaylists(QString);
    bool compare();
public:
    PlaylistChecker(Authorizer * auth, User * user, DatabaseAPI * db);
    void fetch(QString);
};

#endif // PLAYLISTCHECKER_H
