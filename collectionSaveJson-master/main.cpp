#include "mainwindow.h"
#include <QApplication>
#include "server.h"
#include <QtCore/QDebug>
#include <QtCore/QJsonDocument>
#include <QtCore/QCoreApplication>
#include <QMap>
#include <QFile>

// Network
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
