#ifndef WIDGETITEM_H
#define WIDGETITEM_H

#include <QWidget>

namespace Ui {
class WidgetItem;
}

class WidgetItem : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetItem(QWidget *parent = nullptr);
    ~WidgetItem();

private:
    Ui::WidgetItem *ui;
};

#endif // WIDGETITEM_H
