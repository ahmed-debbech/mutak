#include "widgetitem.h"
#include "ui_widgetitem.h"

WidgetItem::WidgetItem(Track & t, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetItem)
{
    ui->setupUi(this);
    ui->playButton->setIcon(QPixmap("://resources/play_button.png"));
    ui->photo->setPixmap(QPixmap("://resources/unloaded.png"));
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
    ui->playedat->setText(t.getPlayDate());

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
