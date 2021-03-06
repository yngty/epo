#include "mainwindow.h"
#include "weibotimelineview.h"
#include "oauthdialog.h"
#include "networkmanager.h"
#include "weibotimeline.h"

#include <QVBoxLayout>
#include <QUrl>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QVector>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    timelineView(new WeiboTimelineView(this))
{
    initUI();

}

void MainWindow::initUI()
{
    setFixedSize(500, 500);
    setCentralWidget(timelineView);

    OauthDialog dialog;
    dialog.exec();

    timelineView->reloadData();

}
