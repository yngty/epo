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
};

#endif // OAUTHDIALOG_H
