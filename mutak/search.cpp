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
void MainWindow::refreshSearch(){
    int index = ui->searchBy->currentIndex();
    vector <Track> t;
    if(index == 0){
        //search by song name
            for(int i=0; i<=tracks.size()-1; i++){
                if(ui->search_text->text().startsWith(tracks[i].getName()) == true){
                    t.push_back(tracks[i]);
                }
            }
    }else{
        //search by artist name
        for(int i=0; i<=tracks.size()-1; i++){
            if(tracks[i].getArtist() == ui->search_text->text()){
                t.push_back(tracks[i]);
            }
        }
    }
    this->addToList(t);
}
