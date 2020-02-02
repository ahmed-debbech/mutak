#ifndef RETRIVEPHOTOSTHREAD_H
#define RETRIVEPHOTOSTHREAD_H

#include <QThread>
#include "photodownloader.h"
#include "widgetitem.h"
#include "ui_widgetitem.h"
#include <QPixmap>

class retrivePhotosThread : public QThread{
    photoDownloader * pd;
public:
    retrivePhotosThread(QString t);
    ~retrivePhotosThread();
    virtual void run(WidgetItem *i);
};

#endif // RETRIVEPHOTOSTHREAD_H
