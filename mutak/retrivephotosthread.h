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
  explicit photoDownloader(QUrl imageUrl, QObject *parent = 0);
  virtual ~photoDownloader();
  QByteArray downloadedData() const;

 signals:
  void downloaded();

 private:
  QNetworkAccessManager m_WebCtrl;
  QByteArray m_DownloadedData;
};

class retrivePhotosThread : public QThread{
    photoDownloader * pd;
public:
    retrivePhotosThread(QString t);
    ~retrivePhotosThread();
    virtual void run(WidgetItem *i);
    virtual void run(QLabel * q);
};

#endif // RETRIVEPHOTOSTHREAD_H
