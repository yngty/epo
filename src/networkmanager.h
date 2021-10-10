#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    static NetworkManager &instance();

    QByteArray get(const QUrl &url, const QMap<QString, QString> &params, bool isAsync = true);
    QByteArray post(const QUrl &url, const QMap<QString, QString> &params, bool isAsync = true);
public:
    const static QString WeiboApiUrl;
    const static QString AppKey;
    const static QString AppSecret;
    const static QString RedirectUrl;
    const static QString OauthGetCodeUrl;
    const static QString OauthGetAccessTokenUrl;
    const static QString HomeTimelineUrl;
    static QString AccessToken;
    static QString ExpiresIn;
private:
    explicit NetworkManager(QObject *parent = nullptr);
};

#endif // NETWORKMANAGER_H
