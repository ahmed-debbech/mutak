#include "track.h"
#include <QString>

Track :: Track(QString namesong, QString art, double dur,
      QDateTime played, QString link){
    name = namesong;
    artist = art;
    duration = dur;
    playedAt = played;
    linkID = link;
}
Track :: Track(){

}
