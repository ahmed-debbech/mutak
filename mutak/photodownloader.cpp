#include "photodownloader.h"

photoDownloader::photoDownloader(QUrl imageUrl, QObject *parent):QObject(parent){

    connect(&m_WebCtrl, SIGNAL (finished(QNetworkReply*)),
     this, SLOT (fileDownloaded(QNetworkReply*)));

    QNetworkRequest request(imageUrl);
    m_WebCtrl.get(request);

}
photoDownloader ::  ~photoDownloader(){

}
void photoDownloader::fileDownloaded(QNetworkReply* pReply) {
 m_DownloadedData = pReply->readAll();
 //emit a signal
 pReply->deleteLater();
 emit downloaded();
}
QByteArray photoDownloader::downloadedData() const {
  return m_DownloadedData;
}
