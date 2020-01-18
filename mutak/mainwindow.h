#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QOAuth2AuthorizationCodeFlow>
#include "authorizer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    Ui::MainWindow * getUi(){ return ui;}
    bool checkForInternet();
    ~MainWindow();
private slots:
    void on_loginButton_clicked();
    void isGranted();
    void on_refresh_button_clicked();
    void on_refresh_retriv_clicked();
private:
    Ui::MainWindow *ui;
    Authorizer auth;
};
#endif // MAINWINDOW_H
