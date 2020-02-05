#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QOAuth2AuthorizationCodeFlow>
#include "authorizer.h"
#include "user.h"
#include "track.h"
#include "databaseapi.h"
#include <QCloseEvent>

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
    QJsonObject  getFromEndPoint(const QUrl&);
    void dataToTracksObjects(QJsonObject &);
    ~MainWindow();
private slots:
    void on_loginButton_clicked();
    void isGranted();
    void closeEvent (QCloseEvent *event);
    void on_refresh_button_clicked();
    void on_refresh_retriv_clicked();
private:
    void addToList();
    Ui::MainWindow *ui;
    Authorizer auth;
    User * user;
    vector<Track> tracks;
    DatabaseAPI * dbapi;
    bool runningWeb;
};
#endif // MAINWINDOW_H
