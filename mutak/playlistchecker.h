#ifndef PLAYLISTCHECKER_H
#define PLAYLISTCHECKER_H

#include "QJsonObject"
#include "mainwindow.h"

class PlaylistChecker{
    QJsonObject data;
public:
    PlaylistChecker(Authorizer * auth, User * user);
};

#endif // PLAYLISTCHECKER_H
