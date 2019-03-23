
#include "mainwindow.h"
#include <QApplication>
#include "server.h"
#include <QtCore/QDebug>
#include <QtCore/QJsonDocument>
#include <QtCore/QCoreApplication>

// Network
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Server workServer;

    w.show();

    return a.exec();
}
