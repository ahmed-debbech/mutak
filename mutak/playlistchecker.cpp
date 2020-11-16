#include "playlistchecker.h"
#include <iostream>
#include "mainwindow.h"
#include "QJsonDocument"

PlaylistChecker::PlaylistChecker(Authorizer * auth, User * user){
    data = MainWindow::getFromEndPoint(*auth,QUrl("https://api.spotify.com/v1/users/"+user->getId()+"/playlists"),user);
    string strFromObj = QJsonDocument(data).toJson(QJsonDocument::Compact).toStdString().c_str();
    std::cout << strFromObj << std::endl;
}
