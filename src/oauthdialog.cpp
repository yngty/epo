#include "oauthdialog.h"
#include "networkmanager.h"

#include <QWebView>
#include <QUrl>
#include <QVBoxLayout>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>


OauthDialog::OauthDialog(QDialog *parent)
    : QDialog(parent),
      webView(new QWebView(this))
{
    initUI();
    loadUrl();
}

void OauthDialog::initUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(webView);
    setLayout(layout);
}

void OauthDialog::loadUrl()
{
    QUrl url(NetworkManager::OauthGetCodeUrl);
    webView->load(url);
    connect(webView, &QWebView::urlChanged, this, &OauthDialog::onRedirected);
}

void OauthDialog::onRedirected(const QUrl & url)
{
   QString strUrl = url.toString();
   qInfo() << strUrl;
   if (strUrl.contains("code=")) {
       QString code = strUrl.mid(strUrl.lastIndexOf("=") + 1);
       qInfo() << code;

       QMap<QString, QString> params;
       params["client_id"] = NetworkManager::AppKey;
       params["client_secret"] = NetworkManager::AppSecret;
       params["grant_type"] = "authorization_code";
       params["code"] = code;
       params["redirect_uri"] = NetworkManager::RedirectUrl;
       QByteArray response = NetworkManager::instance().post(NetworkManager::OauthGetAccessTokenUrl, params);
       if(!response.isEmpty())
       {
           QJsonParseError jsonError;
           QJsonDocument parseDoc = QJsonDocument::fromJson(response, &jsonError);  // 转化为 JSON 文档
           if (!parseDoc.isNull() && (jsonError.error == QJsonParseError::NoError)) {  // 解析未发生错误
               /// JSON 文档为对象
               if (parseDoc.isObject()) {
                   QJsonObject object = parseDoc.object();
                   if (object.contains("access_token")) {
                       QJsonValue value = object.value("access_token");
                       if (value.isString()) {
                           NetworkManager::AccessToken = value.toString();
                           qInfo() << "AccessToken: " << NetworkManager::AccessToken;
                       }
                   }
               }
           }
       }
       webView->hide();
       this->close();
   }


}
