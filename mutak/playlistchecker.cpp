#include "playlistchecker.h"
#include <iostream>
#include "mainwindow.h"
#include "QJsonDocument"
#include "playlist.h"
#include "QJsonArray"

PlaylistChecker::PlaylistChecker(Authorizer * auth, User * user, vector<Track> ne){
    this->auth = auth;
    this->user = user;
    this->todaySongs = ne;
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
            int size = (ar.at(i).toObject()).value("tracks").toObject().value("total").toInt();
            QString url = (ar.at(i).toObject()).value("tracks").toObject().value("href").toString();
            vector<Track> t = this->fetchTracks(url, size);
            Playlist p(pid,name,desc,ownerId, t);
            v.push_back(p);
        }
        i++;
    }
    return v;
}
vector<Track> PlaylistChecker::fetchTracks(QString url, int size){
    data = MainWindow::getFromEndPoint(*auth,QUrl(url+"?offset=0&limit=" + QString::number(size)),user);
    QJsonObject jb = data, r = data;
    QJsonArray arr;
    vector<Track> tracks;
    if(size == 0){return tracks;}
    for(int i=0; i <= size-1; i++){
        jb = data;
        arr = jb.value("items").toArray();
        jb = (arr.at(i).toObject()).value("track").toObject();
        arr = jb.value("artists").toArray();
        QString artistName = arr.at(0).toObject().value("name").toString();
        QString trackName = jb.value("name").toString();
        double dur = jb.value("duration_ms").toDouble();
        QString play = (r.value("items").toArray()).at(i).toObject().value("played_at").toString();

        //timezone conversion to play date
        QString format = "yyyy-MM-ddTHH:mm:ss.zzzZ";
        QDateTime dt = QDateTime::fromString (play, format);
        QDateTime playtimeConverted = QDateTime(dt.date(), dt.time(), Qt::UTC).toLocalTime();

        jb = jb.value("external_urls").toObject();
        QString link = jb.value("spotify").toString();
        QStringRef substr(&link, 31, (link.size()-1) - 30);
        QString l = substr.toString();
            Track track(trackName,artistName,dur,playtimeConverted,l);
         tracks.push_back(track);
    }
    return tracks;
}
vector<Track> PlaylistChecker :: generateNewTracksList(){
    vector<Track> newTracks;
    if(todaySongs.size() > 0){
        for(int k=0; k<=todaySongs.size()-1; k++){
            bool found = false;
            for(int i=0;( i<=this->owned.size()-1) && (found == false); i++){

                if(owned[i].getTracks().size() > 0){
                    for(int j=0;( j<=owned[i].getTracks().size()-1) && (found == false); j++){
                        if(owned[i].getTracks()[j] == todaySongs[k]){
                            found = true;
                        }
                    }
                }
            }
            if(found == false){
                newTracks.push_back(todaySongs[k]);
                cout << todaySongs[k].getName().toStdString() <<endl;
            }
        }
    }
    return newTracks;
}
vector<Track> PlaylistChecker::fetch(QString uid){
    //TODO get owned playlists
    owned = this->getOwnedPlaylists(uid);
    for(int i=0; i<=owned.size()-1; i++){
        cout << owned[i].getName().toStdString() <<endl;
        for(int j=0; j<=owned[i].getTracks().size()-1; j++){
            cout << owned[i].getTracks()[j].getName().toStdString() <<endl;
        }
    }
    //create a list of new tracks
    return this->generateNewTracksList();
}
