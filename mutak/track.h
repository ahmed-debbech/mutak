/*
    Copyright (c) 2020 Ahmed Debbech

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
 */
/**
 * @file track.h
 *
 * @brief Everything related with tracks data
 *
 * @author Ahmed Debbech
 *
 */
#ifndef TRACK_H
#define TRACK_H
#include <QString>
#include <QDateTime>

/**
 * The default Class that hold each track's data
 * 
 * A very abstract class for track's data representation this is the model of how data is stored after retreived from servers 
 * later it will be transformed into a item widget in the list of tracks.
*/
class Track{
    QString name; ///< the song name of the track
    QString artist; ///< the artist name of the track
    double duration; ///< the duration of the track in (ms)
    QDateTime playedAt; ///< the data when the song was played in 
    QString linkID; ///< the link ID used for the uniquness of the song in Spotify
public:
    Track(QString namesong, QString artist, double duration,
          QDateTime playedAt, QString linkID);
    Track();
    QString getName(){return name;}
    QString getArtist(){return artist;}
   double getDuration(){return duration;}
    QDateTime getPlayDate(){return playedAt;}
    QString getID(){ return linkID;}
    bool operator!=(Track t);
};

#endif // TRACK_H
