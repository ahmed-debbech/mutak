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
#include "playlist.h"
#include "ui_widgetitem.h"
#include "widgetitem.h"
#include <iostream>
#include <QDesktopServices>
#include <QUrl>
#include <QComboBox>

WidgetItem::WidgetItem(QLabel *feedback, Authorizer * auth, User * user, int type, Track & t,vector<Playlist> playlist ,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetItem)
{
    ui->setupUi(this);
    ui->playButton->setIcon(QPixmap("://resources/play_button.png"));
    ui->photo->setPixmap(QPixmap("://resources/unloaded.png"));
    ui->id_track->setHidden(true);
    this->playlists = playlist;
    this->track = t;
    this->auth = auth;
    this->feedback = feedback;
    this->user = user;
    if(t.getName().size() <= 32){
        ui->name->setText(t.getName());
    }else{
        QString n = t.getName();
        QStringRef substr(&n, 0, 29);
        QString l = substr.toString() + "...";
        ui->name->setText(QObject::tr(l.toStdString().c_str()));
        ui->name->setToolTip(t.getName());
    }
    ui->name->setStyleSheet("color: #1db954;\nfont: bold 9pt  '://resources/fonts/Gotham-Bold.otf';");
    if(t.getArtist().size() <= 32){
        ui->artist->setText(t.getArtist());
    }else{
        QString n = t.getArtist();
        QStringRef substr(&n, 0, 29);
        QString l = substr.toString() + "...";
        ui->artist->setText(l);
        ui->artist->setStyleSheet("color: white;\n font: bold 12pt  '://resources/fonts/Gotham-Thin.otf';");
        ui->artist->setToolTip(t.getArtist());
    }
    ui->duration->setText(this->convertToMin(static_cast<int>(t.getDuration())));
    ui->playedat->setText(t.getPlayDate().toString());
    ui->id_track->setText(t.getID());
    if(type == 2){
            QComboBox * qcb = new QComboBox();

            qcb->setStyleSheet("QComboBox{ color: white; background-color: #393939; border-radius: 25px; font: bold 14px '://resources/fonts/Gotham-UltraItalic.otf'; border: none; padding: 20px; width: 10px; height: 20px; opacity: 0.7; } "
                               "QComboBox:hover { background-color: #3AE476; } QComboBox:pressed{ background-color: #2BB85D; } ");
            qcb->addItem("Add");
            qcb->setCurrentText("Add");
            for(int i=0; i<=playlist.size()-1; i++){
                   qcb->addItem(playlist[i].getName());
            }
          //connect(qcb, SIGNAL(currentTextChanged(QString)),
            //       this, SLOT(this->itemChanged(QString)));
           connect(qcb, &QComboBox::currentTextChanged,
                [=](QString index){ this->itemChanged(index); });
            qDebug() << "in constructor";
           this->layout()->addWidget(qcb);
            this->layout()->addWidget(qcb);
    }
}
void WidgetItem::itemChanged(QString text){
        //get the playlist id first
        QString id = "";
        for(int i=0; i<=playlists.size()-1; i++){
                if(playlists[i].getName() == text){
                        id = playlists[i].getId();
                        break;
                }
        }
        qDebug() << track.getID();
        QString c = "https://api.spotify.com/v1/playlists/"+id + "/tracks?uris=spotify%3Atrack%3A"+ track.getID();
        qDebug() << c ;
        QJsonObject js = auth->postFromEndPoint(*auth,c, user);
        cout<< js.count();
        this->setStyleSheet("background-color: #484848;");
        this->feedback->setText(track.getName() + " was added to " + text);
}
WidgetItem :: WidgetItem(WidgetItem * item) : ui(new Ui::WidgetItem){
    ui->setupUi(this);
    ui->playButton->setIcon(QPixmap("://resources/play_button.png"));
    const QPixmap* pixmap = item->getUi()->photo->pixmap();
    QImage image( pixmap->toImage() );
    ui->photo->setPixmap(QPixmap::fromImage(image));
    ui->id_track->setHidden(true);
    ui->name->setText(QObject::tr(item->getUi()->name->text().toStdString().c_str()));

    ui->name->setStyleSheet("color: #1db954;\nfont: bold 9pt  '://resources/fonts/Gotham-Bold.otf';");
    ui->artist->setText(item->getUi()->artist->text());
    ui->duration->setText(item->getUi()->duration->text());
    ui->playedat->setText(item->getUi()->playedat->text());
    ui->id_track->setText(item->getUi()->id_track->text());
}
void WidgetItem::on_playButton_clicked(){
    QString url;
    url = "https://open.spotify.com/track/";
    url = url + ui->id_track->text();
    QDesktopServices::openUrl(QUrl(url, QUrl::TolerantMode));
}
QString WidgetItem :: convertToMin(int millsec){
    QTime time(0,0,0);
    time = time.addMSecs(millsec);
    QString r;
    r = time.toString();
    QStringRef substr(&r, 3, r.size()-2);
    r = substr.toString();
    return r;
}
WidgetItem::~WidgetItem()
{
    delete ui;
}
