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
#include "widgetitem.h"
#include "ui_widgetitem.h"
#include <iostream>
#include <QDesktopServices>
#include <QUrl>

WidgetItem::WidgetItem(Track & t, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetItem)
{
    ui->setupUi(this);
    ui->playButton->setIcon(QPixmap("://resources/play_button.png"));
    ui->photo->setPixmap(QPixmap("://resources/unloaded.png"));
    ui->id_track->setHidden(true);
    if(t.getName().size() <= 32){
        ui->name->setText(t.getName());
    }else{
        QString n = t.getName();
        QStringRef substr(&n, 0, 29);
        QString l = substr.toString() + "...";
        ui->name->setText(l);
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
}
WidgetItem :: WidgetItem(WidgetItem * item) : ui(new Ui::WidgetItem){
    ui->setupUi(this);
    ui->playButton->setIcon(QPixmap("://resources/play_button.png"));
    const QPixmap* pixmap = item->getUi()->photo->pixmap();
    QImage image( pixmap->toImage() );
    ui->photo->setPixmap(QPixmap::fromImage(image));
    ui->id_track->setHidden(true);
    ui->name->setText(item->getUi()->name->text());

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
