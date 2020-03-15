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

class retrivePhotosThread : public QThread{
    photoDownloader * pd;
    QString downloadLink;
    WidgetItem * currentItem;
    QByteArray downData;
public:
    retrivePhotosThread(QString t, WidgetItem * i);
    retrivePhotosThread(QString q);
    ~retrivePhotosThread();
    virtual void run();
    QByteArray downloadedData(){return downData;}
};

#endif // RETRIVEPHOTOSTHREAD_H
