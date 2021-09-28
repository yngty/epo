#include "mainwindow.h"
#include "weibotimelineview.h"

#include <QVBoxLayout>

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
}
