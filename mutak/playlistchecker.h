#ifndef PLAYLISTCHECKER_H
#define PLAYLISTCHECKER_H

#include "QJsonObject"
#include "mainwindow.h"
#include "playlist.h"

class PlaylistChecker{
private:
    QJsonObject data;
    vector<Playlist> owned;

    vector<Playlist> getOwnedPlaylists(QString);
public:
    PlaylistChecker(Authorizer * auth, User * user);
    void fetch(QString);
};

#endif // PLAYLISTCHECKER_H
