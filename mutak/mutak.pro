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

SOURCES += \
    aboutwindow.cpp \
    authorizer.cpp \
    databaseapi.cpp \
    exceptionerror.cpp \
    helpwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    openssl-1.1.1d-win32-mingw/include/openssl/applink.c \
    retrivephotosthread.cpp \
    settingswindow.cpp \
    track.cpp \
    user.cpp \
    widgetitem.cpp

HEADERS += \
    authorizer.h \
    databaseapi.h \
    exceptionerror.h \
    mainwindow.h \
    openssl-1.1.1d-win32-mingw/include/openssl/aes.h \
    openssl-1.1.1d-win32-mingw/include/openssl/asn1.h \
    openssl-1.1.1d-win32-mingw/include/openssl/asn1_mac.h \
    openssl-1.1.1d-win32-mingw/include/openssl/asn1err.h \
    openssl-1.1.1d-win32-mingw/include/openssl/asn1t.h \
    openssl-1.1.1d-win32-mingw/include/openssl/async.h \
    openssl-1.1.1d-win32-mingw/include/openssl/asyncerr.h \
    openssl-1.1.1d-win32-mingw/include/openssl/bio.h \
    openssl-1.1.1d-win32-mingw/include/openssl/bioerr.h \
    openssl-1.1.1d-win32-mingw/include/openssl/blowfish.h \
    openssl-1.1.1d-win32-mingw/include/openssl/bn.h \
    openssl-1.1.1d-win32-mingw/include/openssl/bnerr.h \
    openssl-1.1.1d-win32-mingw/include/openssl/buffer.h \
    openssl-1.1.1d-win32-mingw/include/openssl/buffererr.h \
    openssl-1.1.1d-win32-mingw/include/openssl/camellia.h \
    openssl-1.1.1d-win32-mingw/include/openssl/cast.h \
    openssl-1.1.1d-win32-mingw/include/openssl/cmac.h \
    openssl-1.1.1d-win32-mingw/include/openssl/cms.h \
    openssl-1.1.1d-win32-mingw/include/openssl/cmserr.h \
    openssl-1.1.1d-win32-mingw/include/openssl/comp.h \
    openssl-1.1.1d-win32-mingw/include/openssl/comperr.h \
    openssl-1.1.1d-win32-mingw/include/openssl/conf.h \
    openssl-1.1.1d-win32-mingw/include/openssl/conf_api.h \
    openssl-1.1.1d-win32-mingw/include/openssl/conferr.h \
    openssl-1.1.1d-win32-mingw/include/openssl/crypto.h \
    openssl-1.1.1d-win32-mingw/include/openssl/cryptoerr.h \
    openssl-1.1.1d-win32-mingw/include/openssl/ct.h \
    openssl-1.1.1d-win32-mingw/include/openssl/cterr.h \
    openssl-1.1.1d-win32-mingw/include/openssl/des.h \
    openssl-1.1.1d-win32-mingw/include/openssl/dh.h \
    openssl-1.1.1d-win32-mingw/include/openssl/dherr.h \
    openssl-1.1.1d-win32-mingw/include/openssl/dsa.h \
    openssl-1.1.1d-win32-mingw/include/openssl/dsaerr.h \
    openssl-1.1.1d-win32-mingw/include/openssl/dtls1.h \
    openssl-1.1.1d-win32-mingw/include/openssl/e_os2.h \
    openssl-1.1.1d-win32-mingw/include/openssl/ebcdic.h \
    openssl-1.1.1d-win32-mingw/include/openssl/ec.h \
    openssl-1.1.1d-win32-mingw/include/openssl/ecdh.h \
    openssl-1.1.1d-win32-mingw/include/openssl/ecdsa.h \
    openssl-1.1.1d-win32-mingw/include/openssl/ecerr.h \
    openssl-1.1.1d-win32-mingw/include/openssl/engine.h \
    openssl-1.1.1d-win32-mingw/include/openssl/engineerr.h \
    openssl-1.1.1d-win32-mingw/include/openssl/err.h \
    openssl-1.1.1d-win32-mingw/include/openssl/evp.h \
    openssl-1.1.1d-win32-mingw/include/openssl/evperr.h \
    openssl-1.1.1d-win32-mingw/include/openssl/hmac.h \
    openssl-1.1.1d-win32-mingw/include/openssl/idea.h \
    openssl-1.1.1d-win32-mingw/include/openssl/kdf.h \
    openssl-1.1.1d-win32-mingw/include/openssl/kdferr.h \
    openssl-1.1.1d-win32-mingw/include/openssl/lhash.h \
    openssl-1.1.1d-win32-mingw/include/openssl/md2.h \
    openssl-1.1.1d-win32-mingw/include/openssl/md4.h \
    openssl-1.1.1d-win32-mingw/include/openssl/md5.h \
    openssl-1.1.1d-win32-mingw/include/openssl/mdc2.h \
    openssl-1.1.1d-win32-mingw/include/openssl/modes.h \
    openssl-1.1.1d-win32-mingw/include/openssl/obj_mac.h \
    openssl-1.1.1d-win32-mingw/include/openssl/objects.h \
    openssl-1.1.1d-win32-mingw/include/openssl/objectserr.h \
    openssl-1.1.1d-win32-mingw/include/openssl/ocsp.h \
    openssl-1.1.1d-win32-mingw/include/openssl/ocsperr.h \
    openssl-1.1.1d-win32-mingw/include/openssl/opensslconf.h \
    openssl-1.1.1d-win32-mingw/include/openssl/opensslv.h \
    openssl-1.1.1d-win32-mingw/include/openssl/ossl_typ.h \
    openssl-1.1.1d-win32-mingw/include/openssl/pem.h \
    openssl-1.1.1d-win32-mingw/include/openssl/pem2.h \
    openssl-1.1.1d-win32-mingw/include/openssl/pemerr.h \
    openssl-1.1.1d-win32-mingw/include/openssl/pkcs12.h \
    openssl-1.1.1d-win32-mingw/include/openssl/pkcs12err.h \
    openssl-1.1.1d-win32-mingw/include/openssl/pkcs7.h \
    openssl-1.1.1d-win32-mingw/include/openssl/pkcs7err.h \
    openssl-1.1.1d-win32-mingw/include/openssl/rand.h \
    openssl-1.1.1d-win32-mingw/include/openssl/rand_drbg.h \
    openssl-1.1.1d-win32-mingw/include/openssl/randerr.h \
    openssl-1.1.1d-win32-mingw/include/openssl/rc2.h \
    openssl-1.1.1d-win32-mingw/include/openssl/rc4.h \
    openssl-1.1.1d-win32-mingw/include/openssl/rc5.h \
    openssl-1.1.1d-win32-mingw/include/openssl/ripemd.h \
    openssl-1.1.1d-win32-mingw/include/openssl/rsa.h \
    openssl-1.1.1d-win32-mingw/include/openssl/rsaerr.h \
    openssl-1.1.1d-win32-mingw/include/openssl/safestack.h \
    openssl-1.1.1d-win32-mingw/include/openssl/seed.h \
    openssl-1.1.1d-win32-mingw/include/openssl/sha.h \
    openssl-1.1.1d-win32-mingw/include/openssl/srp.h \
    openssl-1.1.1d-win32-mingw/include/openssl/srtp.h \
    openssl-1.1.1d-win32-mingw/include/openssl/ssl.h \
    openssl-1.1.1d-win32-mingw/include/openssl/ssl2.h \
    openssl-1.1.1d-win32-mingw/include/openssl/ssl3.h \
    openssl-1.1.1d-win32-mingw/include/openssl/sslerr.h \
    openssl-1.1.1d-win32-mingw/include/openssl/stack.h \
    openssl-1.1.1d-win32-mingw/include/openssl/store.h \
    openssl-1.1.1d-win32-mingw/include/openssl/storeerr.h \
    openssl-1.1.1d-win32-mingw/include/openssl/symhacks.h \
    openssl-1.1.1d-win32-mingw/include/openssl/tls1.h \
    openssl-1.1.1d-win32-mingw/include/openssl/ts.h \
    openssl-1.1.1d-win32-mingw/include/openssl/tserr.h \
    openssl-1.1.1d-win32-mingw/include/openssl/txt_db.h \
    openssl-1.1.1d-win32-mingw/include/openssl/ui.h \
    openssl-1.1.1d-win32-mingw/include/openssl/uierr.h \
    openssl-1.1.1d-win32-mingw/include/openssl/whrlpool.h \
    openssl-1.1.1d-win32-mingw/include/openssl/x509.h \
    openssl-1.1.1d-win32-mingw/include/openssl/x509_vfy.h \
    openssl-1.1.1d-win32-mingw/include/openssl/x509err.h \
    openssl-1.1.1d-win32-mingw/include/openssl/x509v3.h \
    openssl-1.1.1d-win32-mingw/include/openssl/x509v3err.h \
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

DISTFILES += \
    .gitignore \
    openssl-1.1.1d-win32-mingw/BUILD-HOMEPAGE.url \
    openssl-1.1.1d-win32-mingw/BUILD-README.txt \
    openssl-1.1.1d-win32-mingw/CHANGES.txt \
    openssl-1.1.1d-win32-mingw/FAQ.txt \
    openssl-1.1.1d-win32-mingw/LICENSE.txt \
    openssl-1.1.1d-win32-mingw/NEWS.txt \
    openssl-1.1.1d-win32-mingw/README.txt \
    openssl-1.1.1d-win32-mingw/ct_log_list.cnf \
    openssl-1.1.1d-win32-mingw/ct_log_list.cnf.dist \
    openssl-1.1.1d-win32-mingw/engines-1_1/capi.dll \
    openssl-1.1.1d-win32-mingw/engines-1_1/padlock.dll \
    openssl-1.1.1d-win32-mingw/lib/libcrypto.a \
    openssl-1.1.1d-win32-mingw/lib/libcrypto.dll.a \
    openssl-1.1.1d-win32-mingw/lib/libssl.a \
    openssl-1.1.1d-win32-mingw/lib/libssl.dll.a \
    openssl-1.1.1d-win32-mingw/lib/pkgconfig/libcrypto.pc \
    openssl-1.1.1d-win32-mingw/lib/pkgconfig/libssl.pc \
    openssl-1.1.1d-win32-mingw/lib/pkgconfig/openssl.pc \
    openssl-1.1.1d-win32-mingw/libcrypto-1_1.dll \
    openssl-1.1.1d-win32-mingw/libssl-1_1.dll \
    openssl-1.1.1d-win32-mingw/openssl.cnf \
    openssl-1.1.1d-win32-mingw/openssl.cnf.dist \
    openssl-1.1.1d-win32-mingw/openssl.exe \
    resources/spotifyico.png

