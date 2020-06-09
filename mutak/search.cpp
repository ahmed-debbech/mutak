#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_search_button_clicked(){
    ui->menuBar2->setHidden(false);
    ui->menuBar1->setHidden(true);
    ui->search_list->setHidden(false);
    ui->listWidget->setHidden(true);
}
void MainWindow::on_cancel_search_clicked(){
    ui->menuBar2->setHidden(true);
    ui->menuBar1->setHidden(false);
    ui->search_list->setHidden(true);
    ui->listWidget->setHidden(false);
}
/*bool MainWindow::checkEqualDates(QDateTime textDate, QDate currentPageDate){
    int y,m,d;
    currentPageDate.getDate( &y, &m, &d);
    QDate date = textDate.date();
    if(currentPageDate == date){
        return true;
    }
    return false;
}*/
void MainWindow::refreshSearch(){
    int index = ui->searchBy->currentIndex();
    int y,d,m;
    vector <WidgetItem*> t;
    if(widitem.size() > 0){
        if(index == 0){
            //search by song name
                for(int i=0; i<=widitem.size()-1; i++){
                    Ui::WidgetItem * uiWid = widitem[i]->getUi();
                    if(uiWid->name->text().toLower().startsWith(ui->search_text->text().toLower())){
                        t.push_back(widitem[i]);
                    }
                }
        }else{
            //search by artist name
            for(int i=0; i<=widitem.size()-1; i++){
                Ui::WidgetItem * uiWid = widitem[i]->getUi();
                if(uiWid->artist->text().toLower().startsWith(ui->search_text->text().toLower())){
                    t.push_back(widitem[i]);
                }
            }
        }
    }
    this->showSearchResult(t);
}
void MainWindow :: showSearchResult(vector<WidgetItem*> t){

    //this is memory enhancment: we clear the old widget pointers to avoid memory leaks
    if(this->widitem.size() > 0){
        for (int i=0; i<=this->widitem.size()-1; i++) {
           delete widitem[i];
        }
        this->widitem.clear();
        ui->listWidget->clear();
        std::cout << "cleared" << std::endl;
    }
    //end of memory enhancment

    if(t.size() > 0){
        for(int i=0; i<=t.size()-1; i++){
            cout << "artist: " << t[i]->getUi()->name->text().toStdString() << "song: " << t[i]->getUi()->artist->text().toStdString()<<std::endl;
            QListWidgetItem * lwi = new QListWidgetItem(ui->listWidget);
            ui->listWidget->addItem(lwi);
            lwi->setSizeHint (t[i]->sizeHint());
            ui->listWidget->setItemWidget(lwi, t[i]);
        }
    }
}
