/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout_4;
    QLabel *label;
    QSpacerItem *verticalSpacer_2;
    QPushButton *loginButton;
    QSpacerItem *verticalSpacer;
    QPlainTextEdit *plainTextEdit;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QLabel *photo;
    QSpacerItem *horizontalSpacer_2;
    QLabel *disp_name;
    QSpacerItem *horizontalSpacer;
    QPushButton *refresh_button;
    QPushButton *logout_button;
    QListWidget *listWidget;
    QWidget *page_3;
    QVBoxLayout *verticalLayout_5;
    QLabel *error_retriv;
    QPushButton *refresh_retriv;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(662, 733);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        verticalLayout_4 = new QVBoxLayout(page);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label = new QLabel(page);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font.setPointSize(24);
        label->setFont(font);

        verticalLayout_4->addWidget(label, 0, Qt::AlignHCenter);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_4->addItem(verticalSpacer_2);

        loginButton = new QPushButton(page);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(loginButton->sizePolicy().hasHeightForWidth());
        loginButton->setSizePolicy(sizePolicy);

        verticalLayout_4->addWidget(loginButton, 0, Qt::AlignHCenter);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_4->addItem(verticalSpacer);

        plainTextEdit = new QPlainTextEdit(page);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(plainTextEdit->sizePolicy().hasHeightForWidth());
        plainTextEdit->setSizePolicy(sizePolicy1);

        verticalLayout_4->addWidget(plainTextEdit);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        verticalLayout_2 = new QVBoxLayout(page_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        photo = new QLabel(page_2);
        photo->setObjectName(QString::fromUtf8("photo"));

        horizontalLayout->addWidget(photo);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        disp_name = new QLabel(page_2);
        disp_name->setObjectName(QString::fromUtf8("disp_name"));

        horizontalLayout->addWidget(disp_name);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        refresh_button = new QPushButton(page_2);
        refresh_button->setObjectName(QString::fromUtf8("refresh_button"));

        horizontalLayout->addWidget(refresh_button);

        logout_button = new QPushButton(page_2);
        logout_button->setObjectName(QString::fromUtf8("logout_button"));

        horizontalLayout->addWidget(logout_button);


        verticalLayout_3->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout_3);

        listWidget = new QListWidget(page_2);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        verticalLayout_2->addWidget(listWidget);

        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        verticalLayout_5 = new QVBoxLayout(page_3);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        error_retriv = new QLabel(page_3);
        error_retriv->setObjectName(QString::fromUtf8("error_retriv"));

        verticalLayout_5->addWidget(error_retriv, 0, Qt::AlignHCenter);

        refresh_retriv = new QPushButton(page_3);
        refresh_retriv->setObjectName(QString::fromUtf8("refresh_retriv"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(refresh_retriv->sizePolicy().hasHeightForWidth());
        refresh_retriv->setSizePolicy(sizePolicy2);

        verticalLayout_5->addWidget(refresh_retriv, 0, Qt::AlignHCenter);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Minimum);

        verticalLayout_5->addItem(verticalSpacer_3);

        stackedWidget->addWidget(page_3);

        verticalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Welcome to Mutak", nullptr));
        loginButton->setText(QCoreApplication::translate("MainWindow", "log in", nullptr));
        photo->setText(QCoreApplication::translate("MainWindow", "image", nullptr));
        disp_name->setText(QCoreApplication::translate("MainWindow", "name", nullptr));
        refresh_button->setText(QCoreApplication::translate("MainWindow", "Refresh", nullptr));
        logout_button->setText(QCoreApplication::translate("MainWindow", "Log out", nullptr));
        error_retriv->setText(QCoreApplication::translate("MainWindow", "Could not retrive data please refresh again, check your internet connection", nullptr));
        refresh_retriv->setText(QCoreApplication::translate("MainWindow", "Refresh", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
