// main.cpp

#include <QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QMap <QString,QVariant> mp;
    mp.insert("auth","null");
    mp.insert("hello","world");
    // Make a server and starts it
    MyServer server;
    server.startServer(6000,mp);

    return a.exec();
}
