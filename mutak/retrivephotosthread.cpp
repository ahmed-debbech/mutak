#include "retrivephotosthread.h"
#include <iostream>

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
    std::cout << "run photo" << "\n";
    QPixmap pix;
    pix.loadFromData(pd->downloadedData());
    pix = pix.scaled(64,64,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    q->setPixmap(pix);
}
