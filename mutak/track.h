#ifndef TRACK_H
#define TRACK_H
#include <QString>

class Track{
    QString name;
    QString artist;
    unsigned long long int duration;
    QString playedAt;
    QString linkID;
public:
    Track(QString name, QString artist, unsigned long long int duration,
          QString playedAt, QString linkID);
    QString getName(){return name;}
    QString getArtist(){return artist;}
    unsigned long long int getDuration(){return duration;}
    QString getPlayDate(){return playedAt;}
    QString getLink(){ return linkID;}
};

#endif // TRACK_H
