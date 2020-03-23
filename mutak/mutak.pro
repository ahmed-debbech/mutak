QT       += core gui network networkauth
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++11 openssl-linked

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutwindow.cpp \
    authorizer.cpp \
    databaseapi.cpp \
    helpwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    retrivephotosthread.cpp \
    settingswindow.cpp \
    track.cpp \
    user.cpp \
    widgetitem.cpp

HEADERS += \
    authorizer.h \
    databaseapi.h \
    mainwindow.h \
    retrivephotosthread.h \
    track.h \
    user.h \
    widgetitem.h

FORMS += \
    mainwindow.ui \
    widgetitem.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

LIBS += -L/OpenSSL-Win32/libcrypto-1_1.lib
LIBS += -L/OpenSSL-Win32/libssl-1_1.lib

DISTFILES += \
    .gitignore \
    resources/spotifyico.png \
    OpenSSL-Win32/CA.pl \
    OpenSSL-Win32/PEM/ca-cert.srl \
    OpenSSL-Win32/PEM/ca-key.pem \
    OpenSSL-Win32/PEM/ca-req.pem \
    OpenSSL-Win32/PEM/cert.pem \
    OpenSSL-Win32/PEM/client.pem \
    OpenSSL-Win32/PEM/demoSRP/srp_verifier.txt \
    OpenSSL-Win32/PEM/demoSRP/srp_verifier.txt.attr \
    OpenSSL-Win32/PEM/dh1024.pem \
    OpenSSL-Win32/PEM/dh2048.pem \
    OpenSSL-Win32/PEM/dh4096.pem \
    OpenSSL-Win32/PEM/dsa-ca.pem \
    OpenSSL-Win32/PEM/dsa-pca.pem \
    OpenSSL-Win32/PEM/dsa1024.pem \
    OpenSSL-Win32/PEM/dsa512.pem \
    OpenSSL-Win32/PEM/dsap.pem \
    OpenSSL-Win32/PEM/pca-cert.srl \
    OpenSSL-Win32/PEM/pca-key.pem \
    OpenSSL-Win32/PEM/pca-req.pem \
    OpenSSL-Win32/PEM/privkey.pem \
    OpenSSL-Win32/PEM/req.pem \
    OpenSSL-Win32/PEM/rsa8192.pem \
    OpenSSL-Win32/PEM/s1024key.pem \
    OpenSSL-Win32/PEM/s1024req.pem \
    OpenSSL-Win32/PEM/s512-key.pem \
    OpenSSL-Win32/PEM/s512-req.pem \
    OpenSSL-Win32/PEM/server.pem \
    OpenSSL-Win32/PEM/server.srl \
    OpenSSL-Win32/PEM/server2.pem \
    OpenSSL-Win32/PEM/testCA.pem \
    OpenSSL-Win32/capi.dll \
    OpenSSL-Win32/dasync.dll \
    OpenSSL-Win32/libcrypto-1_1.dll \
    OpenSSL-Win32/libssl-1_1.dll \
    OpenSSL-Win32/openssl.exe \
    OpenSSL-Win32/ossltest.dll \
    OpenSSL-Win32/padlock.dll \
    OpenSSL-Win32/progs.pl \
    OpenSSL-Win32/tsget.pl \

