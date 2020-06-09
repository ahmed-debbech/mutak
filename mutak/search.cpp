#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_search_button_clicked(){
    ui->menuBar2->setHidden(false);
    ui->menuBar1->setHidden(true);
}
void MainWindow::on_cancel_search_clicked(){
    ui->menuBar2->setHidden(true);
    ui->menuBar1->setHidden(false);
}
bool MainWindow::checkEqualDates(QDateTime textDate, QDate currentPageDate){
    int y,m,d;
    currentPageDate.getDate( &y, &m, &d);
    QDate date = textDate.date();
    if(currentPageDate == date){
        return true;
    }
    return false;
}
void MainWindow::refreshSearch(){
    int index = ui->searchBy->currentIndex();
    int y,d,m;
    vector <Track> t;
    if(index == 0){
        //search by song name
            for(int i=0; i<=tracks.size()-1; i++){
                if((checkEqualDates(tracks[i].getPlayDate(), this->currentPageDate) == true) && (tracks[i].getName().toLower().startsWith(ui->search_text->text().toLower()) == true)){
                    t.push_back(tracks[i]);
                }
            }
    }else{
        //search by artist name
        for(int i=0; i<=tracks.size()-1; i++){
            if((checkEqualDates(tracks[i].getPlayDate(), this->currentPageDate) == true) && (tracks[i].getArtist().toLower().startsWith(ui->search_text->text().toLower()) == true)){
                t.push_back(tracks[i]);
            }
        }
    }
    this->addToList(t);
}
