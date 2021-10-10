#include "networkmanager.h"

#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QNetworkReply>

const QString NetworkManager::WeiboApiUrl = "https://api.weibo.com";
const QString NetworkManager::AppKey = "492334311";
const QString NetworkManager::AppSecret = "558ace4cf259ef93e473427cdb19652a";
const QString NetworkManager::RedirectUrl = "https://api.weibo.com/oauth2/default.html";
const QString NetworkManager::OauthGetCodeUrl = WeiboApiUrl + "/oauth2/authorize?client_id=" +
    AppKey + "&redirect_uri=" + RedirectUrl + "&response_type=code";
const QString NetworkManager::OauthGetAccessTokenUrl = WeiboApiUrl + "/oauth2/access_token";
const QString NetworkManager::HomeTimelineUrl = WeiboApiUrl + "/2/statuses/home_timeline.json";
QString NetworkManager::AccessToken = "";
QString NetworkManager::ExpiresIn = "0";

NetworkManager::NetworkManager(QObject *parent) : QObject(parent)
{

}

NetworkManager &NetworkManager::instance()
{
    static NetworkManager manager;
    return manager;
}


QByteArray NetworkManager::get(const QUrl &url, const QMap<QString, QString> &params, bool isAsync)
{

    QNetworkAccessManager manager;
    QEventLoop eventLoop;
    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    QUrl requestUrl = url;
    QNetworkRequest request;


    QByteArray body;
    QMapIterator<QString, QString> i(params);
    while (i.hasNext()) {
        i.next();
        body += QUrl::toPercentEncoding(i.key()) + '=' + QUrl::toPercentEncoding(i.value()) + '&';
    }
    if (!body.isEmpty())
        requestUrl = QUrl(url.toString()+ "?" + QString(body));
     request.setUrl(requestUrl);
    QNetworkReply *reply = manager.get(request);
    if(!isAsync)
        eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    else
        eventLoop.exec();
    QByteArray response;
    if (reply->error() == QNetworkReply::NoError) {
        response = reply->readAll();
    } else {
        //failure
        qInfo() << reply->errorString();
    }
    reply->deleteLater();
    return response;
}

QByteArray NetworkManager::post(const QUrl &url, const QMap<QString, QString> &params, bool isAsync)
{

    QNetworkAccessManager manager;
    QEventLoop eventLoop;
    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    QNetworkRequest request;
    request.setUrl(url);

    QByteArray body;
    QMapIterator<QString, QString> i(params);
    while (i.hasNext()) {
        i.next();
        body += QUrl::toPercentEncoding(i.key()) + '=' + QUrl::toPercentEncoding(i.value()) + '&';
    }
    QNetworkReply *reply = manager.post(request, body);
    if(!isAsync)
        eventLoop.exec(QEventLoop::ExcludeUserInputEvents);
    else
        eventLoop.exec();
    QByteArray response;
    if (reply->error() == QNetworkReply::NoError) {
        response = reply->readAll();
    } else {
        //failure
        qInfo() << reply->errorString();
    }
    reply->deleteLater();
    return response;
}
