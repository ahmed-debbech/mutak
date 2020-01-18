#include "photodownloader.h"
#include <QEventLoop>

photoDownloader::photoDownloader(QUrl imageUrl, QObject *parent):QObject(parent){
    QEventLoop loop;
    connect(&m_WebCtrl, &QNetworkAccessManager::finished,
     this, &photoDownloader::fileDownloaded);

    QNetworkRequest request(imageUrl);
    m_WebCtrl.get(request);
    connect(&m_WebCtrl, &QNetworkAccessManager::finished,
            &loop, &QEventLoop::quit);
    loop.exec();
}
photoDownloader ::  ~photoDownloader(){

}
void photoDownloader::fileDownloaded(QNetworkReply* pReply) {
 m_DownloadedData = pReply->readAll();
 pReply->deleteLater();
}
QByteArray photoDownloader::downloadedData() const {
  return m_DownloadedData;
}
