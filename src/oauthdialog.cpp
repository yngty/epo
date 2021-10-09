#include "oauthdialog.h"
#include <QWebView>
#include <QUrl>
#include <QVBoxLayout>

const QString OauthDialog::WeiboApiUrl = "https://api.weibo.com";
const QString OauthDialog::AppKey = "492334311";
const QString OauthDialog::AppSecret = "558ace4cf259ef93e473427cdb19652a";
const QString OauthDialog::RedirectUrl = "https://api.weibo.com/oauth2/default.html";
const QString OauthDialog::OauthGetCodeUrl = WeiboApiUrl + "/oauth2/authorize?client_id=" +
    AppKey + "&redirect_uri=" + RedirectUrl + "&response_type=code";

QString OauthDialog::AccessToken = "";
QString OauthDialog::ExpiresIn = "0";

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
    QUrl url(OauthGetCodeUrl);
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
   }
   webView->hide();
}
