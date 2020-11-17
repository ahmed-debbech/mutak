#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QString>

class Playlist{
        QString id;
        QString name;
        QString description;
        QString ownerId;
public:
    Playlist(QString id, QString name, QString description, QString ownedId);
    QString getId() const;
    void setId(const QString &value);
    QString getName() const;
    void setName(const QString &value);
    QString getDescription() const;
    void setDescription(const QString &value);
    QString getOwnerId() const;
    void setOwnerId(const QString &value);
};

#endif // PLAYLIST_H
