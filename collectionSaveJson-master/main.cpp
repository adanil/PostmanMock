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
    QString port="";
    QString name="";
    QFile file("C:/Users/Dmitriy Tsuckanov/Documents/postman/collectionSaveJson-master/name.txt");//Относительный путь сюда нужно
    file.open(QFile::ReadOnly | QFile::Text);
    name=file.readAll();
    file.close();
    QFile file2("C:/Users/Dmitriy Tsuckanov/Documents/postman/collectionSaveJson-master/port.txt");//Относительный путь сюда нужно
    file2.open(QFile::ReadOnly | QFile::Text);
    port=file2.readAll();
    file2.close();
    QMap <QString,QString> mp;
    mp.insert("auth","null");
    mp.insert("hello","world");
    Server myServer(0,port.toInt(),name,mp);
    w.show();

    return a.exec();
}
