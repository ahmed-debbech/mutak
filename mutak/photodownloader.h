#ifndef PHOTODOWNLOADER_H
#define PHOTODOWNLOADER_H
#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class photoDownloader : public QObject
{
 Q_OBJECT
 public:
  explicit photoDownloader(QUrl imageUrl, QObject *parent = 0);
  virtual ~photoDownloader();
  QByteArray downloadedData() const;

 signals:
  void downloaded();

 private slots:
  void fileDownloaded(QNetworkReply* pReply);

 private:
  QNetworkAccessManager m_WebCtrl;
  QByteArray m_DownloadedData;
};


#endif // PHOTODOWNLOADER_H
