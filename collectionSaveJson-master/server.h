#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include "mythread.h"
#include <QMap>
#include <QVariant>

class MyServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyServer(QObject *parent = 0);
    void startServer(int port_ = 6000,QMap<QString,QVariant> collection_ = {});
    ~MyServer();
signals:

public slots:

protected:
    void incomingConnection(qintptr socketDescriptor);
    int port;
    QMap<QString,QVariant> collection;
};

#endif // SERVER_H
