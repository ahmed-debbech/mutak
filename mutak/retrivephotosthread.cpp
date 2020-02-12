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
retrivePhotosThread::retrivePhotosThread(QString t){
    pd = new photoDownloader(t);
}
retrivePhotosThread:: ~retrivePhotosThread(){
    delete pd;
}
void retrivePhotosThread :: run(WidgetItem * i){
    Ui::WidgetItem * w = i->getUi();
    QPixmap pix;
    pix.loadFromData(pd->downloadedData());
    w->photo->setPixmap(pix);
}
void retrivePhotosThread :: run(QLabel * q){
    QPixmap pix;
    pix.loadFromData(pd->downloadedData());
    pix = pix.scaled(64,64,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    q->setPixmap(pix);
}
// end of implementation =================================
