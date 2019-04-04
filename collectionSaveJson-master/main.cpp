#include "mainwindow.h"
#include <QApplication>
#include "server.h"
#include <QtCore/QDebug>
#include <QtCore/QJsonDocument>
#include <QtCore/QCoreApplication>
#include <QMap>

// Network
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QMap <QString,QString> mp;
    mp.insert("auth","null");
    mp.insert("hello","world");
    Server myServer(0,6001,"PostmanMockServer",mp);
    w.show();

    return a.exec();
}
