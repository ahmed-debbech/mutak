QT       += core gui network networkauth
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++11
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_ICONS = resources/spotifyico.ico \

SOURCES += \
    aboutwindow.cpp \
    authorizer.cpp \
    databaseapi.cpp \
    exceptionerror.cpp \
    helpwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    playlistchecker.cpp \
    retrivephotosthread.cpp \
    search.cpp \
    settingswindow.cpp \
    track.cpp \
    user.cpp \
    widgetitem.cpp

HEADERS += \
    api_keys.h \
    authorizer.h \
    databaseapi.h \
    exceptionerror.h \
    mainwindow.h \
    playlistchecker.h \
    retrivephotosthread.h \
    track.h \
    user.h \
    widgetitem.h

FORMS += \
    mainwindow.ui \
    widgetitem.ui \
    widgetitem2.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    .gitignore \
    resources/spotifyico.png

