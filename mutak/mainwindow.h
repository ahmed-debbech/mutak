#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QOAuth2AuthorizationCodeFlow>
#include "authorizer.h"
#include "user.h"
#include "track.h"
#include "databaseapi.h"
#include <QCloseEvent>
#include <QDateTime>

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
    void on_navPrev_clicked();
    void on_confirm_clicked();
    void on_navNext_clicked();
    void on_nav_clicked();
    void on_aboutButton_clicked();
    void on_gobackAbout_clicked();
    void on_calendarWidget_selectionChanged();
    void on_settings_button_clicked();
    void on_backFromSettings_clicked();
    void on_logout_button_clicked();
    void on_twitter_clicked();
    void on_github_clicked();
    void on_linkedin_clicked();
    void on_delete_history_clicked();
    void on_website_clicked();
    void on_aboutsettings_clicked();
    void on_helpsettings_clicked();
private:
    struct RecentlyShowedWindows{
        int currentWindowIndex;
        int previousWindowIndex;
    };
    typedef RecentlyShowedWindows recentlyShowedWindows;
    recentlyShowedWindows rsw;
    void addToList(vector <Track> t);
    Ui::MainWindow *ui;
    Authorizer auth;
    User * user;
    vector<Track> tracks;
    DatabaseAPI * dbapi;
    bool runningWeb;
    QDateTime currentPageDate;
};
#endif // MAINWINDOW_H
