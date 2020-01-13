#include "authorizer.h"
#include <QOAuthHttpServerReplyHandler>
#include <QDesktopServices>
#include <QObject>

Authorizer::Authorizer(){
    clientID = "17003af1c95b4506b21dbf98110a6e6f";
    clientSecret = "52291278398442e1961f84615d55a097";
}
void Authorizer :: setValues(){
    auto replyHandler = new QOAuthHttpServerReplyHandler(80, this);
    replyHandler->setCallbackPath("cb");
    spotify.setReplyHandler(replyHandler);
    spotify.setAuthorizationUrl(QUrl("https://accounts.spotify.com/authorize"));
    spotify.setAccessTokenUrl(QUrl("https://accounts.spotify.com/api/token"));
    spotify.setClientIdentifier(clientID);
    spotify.setClientIdentifierSharedKey(clientSecret);
    spotify.setScope("user-read-private user-read-recently-played");
}

void Authorizer :: connectToBrowser(){
    connect(&spotify, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser,
             &QDesktopServices::openUrl);
}

QOAuth2AuthorizationCodeFlow * Authorizer :: getAuthObject(){
    return &spotify;
}
