#include "widgetitem.h"
#include "ui_widgetitem.h"

WidgetItem::WidgetItem(QPixmap & pix, Track & t, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetItem)
{
    ui->setupUi(this);
    ui->photo->setPixmap(pix);
    ui->name->setText(t.getName());
    ui->artist->setText(t.getArtist());
    ui->duration->setText(QString::number(t.getDuration()));
    ui->playedat->setText(t.getPlayDate());
}

WidgetItem::~WidgetItem()
{
    delete ui;
}
