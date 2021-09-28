#include <QApplication>
#include <QTextCodec>
#include "oauthdialog.h"
#include "mainwindow.h"
#include "constants.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));

    MainWindow w;
    w.show();
    return app.exec();
}
