#include "playlist.h"
#include "QString"

QString Playlist::getId() const
{
    return id;
}

void Playlist::setId(const QString &value)
{
    id = value;
}

QString Playlist::getName() const
{
    return name;
}

void Playlist::setName(const QString &value)
{
    name = value;
}

QString Playlist::getDescription() const
{
    return description;
}

void Playlist::setDescription(const QString &value)
{
    description = value;
}

QString Playlist::getOwnerId() const
{
    return ownerId;
}

void Playlist::setOwnerId(const QString &value)
{
    ownerId = value;
}

vector<Track> Playlist::getTracks() const
{
    return tracks;
}

void Playlist::setTracks(const vector<Track> &value)
{
    tracks = value;
}

Playlist::Playlist(QString id, QString name, QString description, QString ownedId, vector<Track> v){
    this->id = id;
    this->name = name;
    this->ownerId = ownedId;
    this->description = description;
    this->tracks = v;
}
