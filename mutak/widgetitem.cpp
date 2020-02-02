#include "widgetitem.h"
#include "ui_widgetitem.h"

WidgetItem::WidgetItem(Track & t, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetItem)
{
    ui->setupUi(this);
    //ui->photo->setPixmap(pix);
    if(t.getName().size() <= 32){
        ui->name->setText(t.getName());
    }else{
        QString n = t.getName();
        QStringRef substr(&n, 0, 29);
        QString l = substr.toString() + "...";
        ui->name->setText(l);
        ui->name->setToolTip(t.getName());
    }
    if(t.getArtist().size() <= 32){
        ui->artist->setText(t.getArtist());
    }else{
        QString n = t.getArtist();
        QStringRef substr(&n, 0, 29);
        QString l = substr.toString() + "...";
        ui->artist->setText(l);
        ui->artist->setToolTip(t.getArtist());
    }
    ui->duration->setText(QString::number(t.getDuration()));
    ui->playedat->setText(t.getPlayDate());
}

WidgetItem::~WidgetItem()
{
    delete ui;
}
