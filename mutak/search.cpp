#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_search_button_clicked(){
    ui->menuBar2->setHidden(false);
    ui->menuBar1->setHidden(true);
    ui->search_list->setHidden(false);
    ui->listWidget->setHidden(true);
    ui->search_tip->setHidden(false);
    ui->search_tip->setText("Type in search bar for song/artist name");
}
void MainWindow::on_cancel_search_clicked(){
    ui->menuBar2->setHidden(true);
    ui->menuBar1->setHidden(false);
    ui->search_list->setHidden(true);
    ui->listWidget->setHidden(false);
    ui->search_tip->setHidden(true);
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
    vector <WidgetItem*> t;
    if(widitem.size() > 0){
        if(index == 0){
            cout << "ttt";
            //search by song name
                for(int i=0; i<=widitem.size()-1; i++){
                    Ui::WidgetItem * uiWid = widitem[i]->getUi();
                       if(ui->search_text->text() != ""){
                        if(uiWid->name->text().toLower().startsWith(ui->search_text->text().toLower())){
                            t.push_back(new WidgetItem(widitem[i]));
                            cout << "rr";
                        }
                       }
                }
        }else{
            //search by artist name
            for(int i=0; i<=widitem.size()-1; i++){
                Ui::WidgetItem * uiWid = widitem[i]->getUi();
                    if(ui->search_text->text() != ""){
                        if(uiWid->artist->text().toLower().startsWith(ui->search_text->text().toLower())){
                            t.push_back(new WidgetItem(widitem[i]));
                        }
                    }
            }
        }
    }
    this->showSearchResult(t);
}
void MainWindow :: showSearchResult(vector<WidgetItem*> t){
        ui->search_list->clear();
        std::cout << "cleared" << std::endl;
    //end of memory enhancment
    if(t.size() > 0){
        cout << "yooo" ;
        for(int i=0; i<=t.size()-1; i++){
            cout << "artist: " << t[i]->getUi()->name->text().toStdString() << "song: " << t[i]->getUi()->artist->text().toStdString()<<std::endl;
            QListWidgetItem * lwi = new QListWidgetItem(ui->search_list);
            ui->search_list->addItem(lwi);
            lwi->setSizeHint (t[i]->sizeHint());
            ui->search_list->setItemWidget(lwi, t[i]);
            ui->search_tip->setHidden(true);
        }
    }
    if(ui->search_text->text() == ""){
        ui->search_tip->setHidden(false);
        ui->search_tip->setText("Type in search bar for song/artist name");
    }else{
        if(ui->search_list->count() == 0){
            std::cout << "reer" <<std::endl;
            ui->search_tip->setHidden(false);
            ui->search_tip->setText("No results for " + ui->search_text->text());
        }
    }
}
