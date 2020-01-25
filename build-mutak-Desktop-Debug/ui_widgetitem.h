/********************************************************************************
** Form generated from reading UI file 'widgetitem.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETITEM_H
#define UI_WIDGETITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetItem
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *photo;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QLabel *name;
    QLabel *artist;
    QVBoxLayout *verticalLayout_2;
    QLabel *duration;
    QLabel *playedat;
    QLabel *play;

    void setupUi(QWidget *WidgetItem)
    {
        if (WidgetItem->objectName().isEmpty())
            WidgetItem->setObjectName(QString::fromUtf8("WidgetItem"));
        WidgetItem->resize(476, 110);
        horizontalLayout = new QHBoxLayout(WidgetItem);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        photo = new QLabel(WidgetItem);
        photo->setObjectName(QString::fromUtf8("photo"));

        horizontalLayout->addWidget(photo);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(WidgetItem);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 106, 68));
        name = new QLabel(scrollAreaWidgetContents);
        name->setObjectName(QString::fromUtf8("name"));
        name->setGeometry(QRect(0, 0, 541, 41));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        artist = new QLabel(WidgetItem);
        artist->setObjectName(QString::fromUtf8("artist"));

        verticalLayout->addWidget(artist);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        duration = new QLabel(WidgetItem);
        duration->setObjectName(QString::fromUtf8("duration"));

        verticalLayout_2->addWidget(duration);

        playedat = new QLabel(WidgetItem);
        playedat->setObjectName(QString::fromUtf8("playedat"));

        verticalLayout_2->addWidget(playedat);


        horizontalLayout->addLayout(verticalLayout_2);

        play = new QLabel(WidgetItem);
        play->setObjectName(QString::fromUtf8("play"));

        horizontalLayout->addWidget(play);


        retranslateUi(WidgetItem);

        QMetaObject::connectSlotsByName(WidgetItem);
    } // setupUi

    void retranslateUi(QWidget *WidgetItem)
    {
        WidgetItem->setWindowTitle(QCoreApplication::translate("WidgetItem", "Form", nullptr));
        photo->setText(QCoreApplication::translate("WidgetItem", "Photo", nullptr));
        name->setText(QCoreApplication::translate("WidgetItem", "name", nullptr));
        artist->setText(QCoreApplication::translate("WidgetItem", "artist", nullptr));
        duration->setText(QCoreApplication::translate("WidgetItem", "duration", nullptr));
        playedat->setText(QCoreApplication::translate("WidgetItem", "played at", nullptr));
        play->setText(QCoreApplication::translate("WidgetItem", "play", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WidgetItem: public Ui_WidgetItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETITEM_H
