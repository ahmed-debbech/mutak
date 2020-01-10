/********************************************************************************
** Form generated from reading UI file 'twitterdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TWITTERDIALOG_H
#define UI_TWITTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_TwitterDialog
{
public:
    QFormLayout *formLayout;
    QLabel *clientIdLabel;
    QLineEdit *clientIdLineEdit;
    QLabel *clientSecretLabel;
    QLineEdit *clientSecretLineEdit;
    QPushButton *pushButton;
    QTableView *view;

    void setupUi(QDialog *TwitterDialog)
    {
        if (TwitterDialog->objectName().isEmpty())
            TwitterDialog->setObjectName(QString::fromUtf8("TwitterDialog"));
        TwitterDialog->resize(800, 600);
        formLayout = new QFormLayout(TwitterDialog);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        clientIdLabel = new QLabel(TwitterDialog);
        clientIdLabel->setObjectName(QString::fromUtf8("clientIdLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, clientIdLabel);

        clientIdLineEdit = new QLineEdit(TwitterDialog);
        clientIdLineEdit->setObjectName(QString::fromUtf8("clientIdLineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, clientIdLineEdit);

        clientSecretLabel = new QLabel(TwitterDialog);
        clientSecretLabel->setObjectName(QString::fromUtf8("clientSecretLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, clientSecretLabel);

        clientSecretLineEdit = new QLineEdit(TwitterDialog);
        clientSecretLineEdit->setObjectName(QString::fromUtf8("clientSecretLineEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, clientSecretLineEdit);

        pushButton = new QPushButton(TwitterDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        formLayout->setWidget(2, QFormLayout::SpanningRole, pushButton);

        view = new QTableView(TwitterDialog);
        view->setObjectName(QString::fromUtf8("view"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(view->sizePolicy().hasHeightForWidth());
        view->setSizePolicy(sizePolicy);
        view->setSelectionMode(QAbstractItemView::NoSelection);
        view->horizontalHeader()->setStretchLastSection(true);
        view->verticalHeader()->setVisible(false);

        formLayout->setWidget(3, QFormLayout::SpanningRole, view);

#if QT_CONFIG(shortcut)
        clientIdLabel->setBuddy(clientIdLineEdit);
        clientSecretLabel->setBuddy(clientSecretLineEdit);
#endif // QT_CONFIG(shortcut)

        retranslateUi(TwitterDialog);

        QMetaObject::connectSlotsByName(TwitterDialog);
    } // setupUi

    void retranslateUi(QDialog *TwitterDialog)
    {
        TwitterDialog->setWindowTitle(QCoreApplication::translate("TwitterDialog", "Twitter Timeline", nullptr));
        clientIdLabel->setText(QCoreApplication::translate("TwitterDialog", "C&lient Id:", nullptr));
        clientSecretLabel->setText(QCoreApplication::translate("TwitterDialog", "Client &secret:", nullptr));
        pushButton->setText(QCoreApplication::translate("TwitterDialog", "&Connect", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TwitterDialog: public Ui_TwitterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TWITTERDIALOG_H
