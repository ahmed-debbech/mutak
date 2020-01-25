#ifndef WIDGETITEM_H
#define WIDGETITEM_H

#include <QWidget>
#include "track.h"
#include <QPixmap>
#include "photodownloader.h"


namespace Ui {
class WidgetItem;
}

class WidgetItem : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetItem(QPixmap &pix, Track &t,QWidget *parent = nullptr);
    ~WidgetItem();

private:
    Ui::WidgetItem *ui;
};

#endif // WIDGETITEM_H
