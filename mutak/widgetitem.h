#ifndef WIDGETITEM_H
#define WIDGETITEM_H

#include <QWidget>
#include "track.h"
#include "photodownloader.h"


namespace Ui {
class WidgetItem;
}

class WidgetItem : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetItem( Track &t,QWidget *parent = nullptr);
    ~WidgetItem();
    Ui::WidgetItem * getUi(){ return ui;}
private:
    Ui::WidgetItem *ui;
};

#endif // WIDGETITEM_H
