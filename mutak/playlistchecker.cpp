#include "playlistchecker.h"
#include <iostream>
#include "mainwindow.h"
#include "QJsonDocument"
#include "playlist.h"
#include "QJsonArray"

PlaylistChecker::PlaylistChecker(Authorizer * auth, User * user){
    data = MainWindow::getFromEndPoint(*auth,QUrl("https://api.spotify.com/v1/users/"+user->getId()+"/playlists?limit=50"),user);
    string strFromObj = QJsonDocument(data).toJson(QJsonDocument::Compact).toStdString().c_str();
    std::cout << strFromObj << std::endl;
}
vector<Playlist> PlaylistChecker :: getOwnedPlaylists(QString uid){
    vector<Playlist> v;
    QJsonObject dataCopy = data;
    int i=0;
    while(i<dataCopy.value("total").toInt()){
        QJsonArray ar;
        ar = dataCopy.value("items").toArray();
        //we check about the ownership first
        QJsonObject owner = (ar.at(i).toObject()).value("owner").toObject();
        if(owner.value("id").toString() == uid){
            //playlist is owned
            QString pid = (ar.at(i).toObject().value("id").toString());
            QString name = (ar.at(i).toObject().value("name").toString());
            QString desc = (ar.at(i).toObject().value("decription").toString());
            QString ownerId = owner.value("id").toString();
            Playlist p(pid,name,desc,ownerId);
            v.push_back(p);
        }
        i++;
    }
    return v;
}
void PlaylistChecker::fetch(QString uid){
    //TODO get owned playlists
    owned = this->getOwnedPlaylists(uid);
    std::cout << owned[0].getId().toStdString()<<std::endl;
    //fetch songs in these playlists
    //create a list of new tracks
    //render item widgets for each track
}
