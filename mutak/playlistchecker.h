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
    vector<Track> todaySongs;

    vector<Track> fetchTracks(QString, int);
    vector<Playlist> getOwnedPlaylists(QString);
    vector<Track> generateNewTracksList();
public:
    PlaylistChecker(Authorizer * auth, User * user, vector<Track>);
    vector<Track> fetch(QString);
};

#endif // PLAYLISTCHECKER_H
