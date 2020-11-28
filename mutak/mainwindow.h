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
 * @file mainwindow.h
 *
 * @brief This is where the main modules of the app live
 *
 * @author Ahmed Debbech
 *
 */
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

/**
 * Main class for everything
 * 
 * This is the first class instantiated when the app launches. It contains everything related with the UI managment and
 * all the slots and signals. It calls all the other modules and classes and it makes the entire workflow.
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    Ui::MainWindow * getUi(){ return ui;}
    void checkForInternet();
    QJsonObject static getFromEndPoint(Authorizer& , const QUrl&, User*);
    QString convertDateToQString(QDate);
    QString convertDateToQString(int, int, int);
    void dataToTracksObjects(QJsonObject &);
    void storeTokens(QString, QString);
    bool restoreTokens();
    void isAlreadyGranted();
    Authorizer * getAuth(){return &auth;}
    User * getUser(){return user;}
    ~MainWindow();
private slots:
    void changeValue();
    void refreshSearch();
    void on_loginButton_clicked();
    void isGranted();
    void closeEvent (QCloseEvent *event);
    void on_refresh_button_clicked();
    void on_stop_button_clicked();
    void on_refresh_retriv_clicked();
    void on_today_clicked();
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
    void on_search_button_clicked();
    void on_cancel_search_clicked();
    void on_helpButton_clicked();
    void on_gobackHelp_clicked();
    void delete_threads(retrivePhotosThread * i);
    void auto_refresh();
    void on_tabWidget_currentChanged(int index);

private:
    //private functions
    void setCalendarMarks();
    void showSearchResult(vector<WidgetItem*> t);
    void getArtworks(vector<Track> t);
    void addToList(vector <Track> t, QListWidget * list);
    long int convertToMS(int index);
    vector<Track>  sortByTime(vector<Track> t);
    void setAutoRefreshTime();

    struct RecentlyShowedWindows{
        int currentWindowIndex;
        int previousWindowIndex;
    };
    typedef RecentlyShowedWindows recentlyShowedWindows; 
    recentlyShowedWindows windowsCursor; ///< the pointer navigation between pages in UI
    Ui::MainWindow *ui; ///< the ui pointer of the whole MUTAK GUI
    Authorizer auth; ///< the authorization object
    User * user; ///< a pointer to the current logged-in user object
    vector<Track> tracks; ///< an array that is used whenever a list should be filled in GUI, represents the data model
    DatabaseAPI * dbapi; ///< the only door that connects the app with the database, a pointer on a DatabaseAPI object that is used for any read/write operation
    bool runningWeb; ///< a boolean variable tells if the application is curently using network or not
    int stopOnClose; ///< a flag that tells to stop using network when the program is terminated
    QTimer * timer; ///< a timer object that is used to track the auto-refresh time to refresh the list when it times out
    QDate currentPageDate; ///< the current date of the day chosen by the calendar navigator
    vector <WidgetItem*> widitem; ///< an array contains a pointers to WidgetItem objects that will be added to a list, represents view model 
    vector<retrivePhotosThread *> runningThreads; ///< an array to store the running threads for the artwork retrieve to allow parallel connections
};
#endif // MAINWINDOW_H
