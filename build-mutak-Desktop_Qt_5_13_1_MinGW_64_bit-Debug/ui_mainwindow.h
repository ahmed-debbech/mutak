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
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label;
    QPushButton *loginButton;
    QPlainTextEdit *plainTextEdit;
    QWidget *page_2;
    QLabel *label_2;
    QLabel *label_3;
    QWidget *page_3;
    QLabel *error_retriv;
    QPushButton *refresh_retriv;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(720, 1000);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 0, 721, 1001));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        label = new QLabel(page);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(90, -20, 611, 211));
        QFont font;
        font.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font.setPointSize(24);
        label->setFont(font);
        loginButton = new QPushButton(page);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));
        loginButton->setGeometry(QRect(260, 260, 211, 81));
        plainTextEdit = new QPlainTextEdit(page);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(90, 440, 511, 131));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        label_2 = new QLabel(page_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 10, 411, 61));
        label_3 = new QLabel(page_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 70, 47, 14));
        stackedWidget->addWidget(page_2);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        error_retriv = new QLabel(page_3);
        error_retriv->setObjectName(QString::fromUtf8("error_retriv"));
        error_retriv->setGeometry(QRect(150, 200, 451, 191));
        refresh_retriv = new QPushButton(page_3);
        refresh_retriv->setObjectName(QString::fromUtf8("refresh_retriv"));
        refresh_retriv->setGeometry(QRect(260, 380, 141, 81));
        stackedWidget->addWidget(page_3);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Welcome to Mutak!", nullptr));
        loginButton->setText(QCoreApplication::translate("MainWindow", "log in", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Name: ", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Id: ", nullptr));
        error_retriv->setText(QCoreApplication::translate("MainWindow", "Could not retrive data please refresh again, check your internet connection", nullptr));
        refresh_retriv->setText(QCoreApplication::translate("MainWindow", "Refresh", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
