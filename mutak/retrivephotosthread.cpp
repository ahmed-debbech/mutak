#include "retrivephotosthread.h"
#include <iostream>

retrivePhotosThread::retrivePhotosThread(QString t){
    pd = new photoDownloader(t);
}
retrivePhotosThread:: ~retrivePhotosThread(){
    delete pd;
}
void retrivePhotosThread :: run(WidgetItem * i){
    std::cout << "runnning " <<std::endl;
    Ui::WidgetItem * w = i->getUi();
    QPixmap pix;
    pix.loadFromData(pd->downloadedData());
    w->photo->setPixmap(pix);
}
