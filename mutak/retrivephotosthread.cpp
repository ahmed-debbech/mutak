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
