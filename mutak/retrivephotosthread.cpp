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
#include "retrivephotosthread.h"
#include <iostream>

//Implementation of downloader class========================================
photoDownloader::photoDownloader(QUrl imageUrl, QObject *parent):QObject(parent){
    QEventLoop loop;
    QNetworkRequest request(imageUrl);
    QNetworkReply * reply = m_WebCtrl.get(request);
    connect(&m_WebCtrl, &QNetworkAccessManager::finished,
            this, [=](){
        m_DownloadedData = reply->readAll();
        reply->deleteLater();
    });
    connect(&m_WebCtrl, &QNetworkAccessManager::finished,
            &loop, &QEventLoop::quit);
    loop.exec();
}

photoDownloader ::  ~photoDownloader(){

}
QByteArray photoDownloader::downloadedData() const {
  return m_DownloadedData;
}
//end of implementation ================================

//Implementation of thread class =========================
retrivePhotosThread::retrivePhotosThread(QString t, WidgetItem * i){
    downloadLink = t;
    currentItem = i;
}
retrivePhotosThread::retrivePhotosThread( QString q, QLabel * p){
    currentItem = nullptr;
    downloadLink = q;
    photo = p;
}
retrivePhotosThread:: ~retrivePhotosThread(){
    delete pd;
}
void retrivePhotosThread :: run(){
    if(currentItem != nullptr){
            pd = new photoDownloader(downloadLink);
            downData = pd->downloadedData();
        Ui::WidgetItem * w = currentItem->getUi();
        QPixmap pix;
        pix.loadFromData(downData);
        w->photo->setPixmap(pix);
    }else{
        pd = new photoDownloader(downloadLink);
        downData = pd->downloadedData();
        QPixmap pix;
        pix.loadFromData(pd->downloadedData());
        pix = pix.scaled(64,64,Qt::KeepAspectRatio,Qt::SmoothTransformation);
        photo->setPixmap(pix);
    }
}
// end of implementation =================================
