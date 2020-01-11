#include "authorizer.h"
#include <QOAuthHttpServerReplyHandler>
#include <QDesktopServices>
#include <QObject>

Authorizer::Authorizer(){
    clientID = "17003af1c95b4506b21dbf98110a6e6f";
    clientSecret = "52291278398442e1961f84615d55a097";
}
void Authorizer :: setValues(QMainWindow * w){

    auto replyHandler = new QOAuthHttpServerReplyHandler(8080, this);
    spotify.setReplyHandler(replyHandler);
    spotify.setAuthorizationUrl(QUrl("https://accounts.spotify.com/authorize"));
    spotify.setAccessTokenUrl(QUrl("https://accounts.spotify.com/api/token"));
    spotify.setClientIdentifier(clientID);
    spotify.setClientIdentifierSharedKey(clientSecret);
    spotify.setScope("user-read-private user-read-recently-played");
    //oauth2.setScope("identity read");

    connect(&spotify, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser,
             &QDesktopServices::openUrl);
}
