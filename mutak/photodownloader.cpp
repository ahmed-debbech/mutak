#include "photodownloader.h"
#include <QEventLoop>

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
