#ifndef TRACK_H
#define TRACK_H
#include <QString>
#include <QDateTime>

class Track{
    QString name;
    QString artist;
    double duration;
    QDateTime playedAt;
    QString linkID;
public:
    Track(QString namesong, QString artist, double duration,
          QDateTime playedAt, QString linkID);
    Track();
    QString getName(){return name;}
    QString getArtist(){return artist;}
   double getDuration(){return duration;}
    QDateTime getPlayDate(){return playedAt;}
    QString getID(){ return linkID;}
};

#endif // TRACK_H
