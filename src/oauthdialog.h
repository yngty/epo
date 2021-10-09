#ifndef OAUTHDIALOG_H
#define OAUTHDIALOG_H

#include <QDialog>

class QWebView;

class OauthDialog : public QDialog
{
    Q_OBJECT
public:
    explicit OauthDialog(QDialog *parent = nullptr);

signals:

public slots:
private slots:
    void onRedirected(const QUrl&);
private:
    void initUI();
    void loadUrl();
private:
    QWebView *webView;

    const static QString WeiboApiUrl;
    const static QString AppKey;
    const static QString AppSecret;
    const static QString RedirectUrl;
    const static QString OauthGetCodeUrl;
    static QString AccessToken;
    static QString ExpiresIn;
};

#endif // OAUTHDIALOG_H
