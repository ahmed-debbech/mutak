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
/**
 * @file widgetitem.h
 *
 * @brief Contains all methodes and functions about widget items 
 *
 * @author Ahmed Debbech
 *
 */
#ifndef WIDGETITEM_H
#define WIDGETITEM_H

#include <QWidget>
#include "track.h"
#include <QTime>

namespace Ui {
class WidgetItem;
}
/**
 * The prototype model class of the item in the List Widget in UI 
 * 
 * This is the User Interface high-level representation of the low-level Track object.
 * It inherits QWidget to behave like a widget in the QT app.
*/
class WidgetItem : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetItem( Track &t,QWidget *parent = nullptr);
    WidgetItem(WidgetItem * item);
    ~WidgetItem();
    Ui::WidgetItem * getUi(){ return ui;}
private slots:
    void on_playButton_clicked();
private:
    QString convertToMin(int millsec);
    Ui::WidgetItem *ui;
};

#endif // WIDGETITEM_H
