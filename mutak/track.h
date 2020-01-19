#ifndef TRACK_H
#define TRACK_H
#include <QString>

class Track{
    QString name;
    QString artist;
    double duration;
    QString playedAt;
    QString linkID;
public:
    Track(QString namesong, QString artist, double duration,
          QString playedAt, QString linkID);
    QString getName(){return name;}
    QString getArtist(){return artist;}
   double getDuration(){return duration;}
    QString getPlayDate(){return playedAt;}
    QString getLink(){ return linkID;}
};

#endif // TRACK_H
