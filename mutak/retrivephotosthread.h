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
 * @file retrivephotosthread.h
 *
 * @brief This contains everything about retreiving photos from the servers
 *
 * @author Ahmed Debbech
 *
 */
#ifndef RETRIVEPHOTOSTHREAD_H
#define RETRIVEPHOTOSTHREAD_H

#include <QThread>
#include "widgetitem.h"
#include "ui_widgetitem.h"
#include <QPixmap>
#include <QNetworkAccessManager>
#include <QNetworkReply>

//this is a key component class for retrivePhotosClass to achive the download properly
class photoDownloader : public QObject{
 Q_OBJECT
 public:
  explicit photoDownloader(QUrl imageUrl, QObject *parent = nullptr);
  virtual ~photoDownloader();
  QByteArray downloadedData() const;

 signals:
  void downloaded();

 private:
  QNetworkAccessManager m_WebCtrl;
  QByteArray m_DownloadedData;
};
/**
 * A basic class that makes a thread for each photo retrive from servers.
 * 
 * This Class creates a thread for each item widget to retrive its artwork image.
 * It inherits QThread to make threading possible in a QT app. When the object is instantiated it
 *  instantiates a photoDownloader object as a pointer
*/
class retrivePhotosThread : public QThread{
    photoDownloader * pd;
    QString downloadLink;
    WidgetItem * currentItem;
    QByteArray downData;
    QLabel * photo;
public:
    retrivePhotosThread(QString t, WidgetItem * i);
    retrivePhotosThread(QString q, QLabel * p);
    ~retrivePhotosThread();
    virtual void run();
};

#endif // RETRIVEPHOTOSTHREAD_H
