#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QObject>

class HttpClient : public QObject
{
    Q_OBJECT
public:
    explicit HttpClient(QObject *parent = nullptr);

signals:

public slots:
};

#endif // HTTPCLIENT_H