/*
    Copyright (c) 2020 Ahmed Debbech

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
 */
#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::on_search_button_clicked(){
    ui->menuBar2->setHidden(false);
    ui->menuBar1->setHidden(true);
    ui->search_list->setHidden(false);
    ui->tabWidget->setHidden(true);
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
    ui->tabWidget->setHidden(false);
}
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
