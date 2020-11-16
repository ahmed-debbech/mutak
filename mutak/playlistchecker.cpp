#include "playlistchecker.h"
#include <iostream>
#include "mainwindow.h"
#include "QJsonDocument"

PlaylistChecker::PlaylistChecker(Authorizer * auth, User * user){
    data = MainWindow::getFromEndPoint(*auth,QUrl("https://api.spotify.com/v1/users/"+user->getId()+"/playlists?limit=50"),user);
    string strFromObj = QJsonDocument(data).toJson(QJsonDocument::Compact).toStdString().c_str();
    std::cout << strFromObj << std::endl;
}
void PlaylistChecker::fetch(){
    //TODO get owned playlists
    //fetch songs in these playlists
    //create a list of new tracks
    //render item widgets for each track
}
