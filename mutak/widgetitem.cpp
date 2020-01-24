#include "widgetitem.h"
#include "ui_widgetitem.h"

WidgetItem::WidgetItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetItem)
{
    ui->setupUi(this);
}

WidgetItem::~WidgetItem()
{
    delete ui;
}
