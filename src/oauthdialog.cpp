#include "oauthdialog.h"
#include <QWebView>
#include <QUrl>
#include <QVBoxLayout>
#include <QOAuth2AuthorizationCodeFlow>

const QString urlStr = "https://api.weibo.com/oauth2/authorize?client_id=492334311&redirect_uri=http://baidu.com&response_type=code";
OauthDialog::OauthDialog(QDialog *parent)
    : QDialog(parent),
      webView(new QWebView(this))
{
//    initUI();
//    loadUrl();
    QOAuth2AuthorizationCodeFlow *weibo = new QOAuth2AuthorizationCodeFlow(this);
//    weibo->grant()
}

void OauthDialog::initUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(webView);
    setLayout(layout);
}

void OauthDialog::loadUrl()
{
    QUrl url(urlStr);
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
}
