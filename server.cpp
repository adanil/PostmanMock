#include "server.h"
#include <QDebug>
#include <QCoreApplication>
#include <QString>
Server::Server(QObject *parent) : QObject(parent)
{
    myServer = new QTcpServer(this);

    connect(myServer, &QTcpServer::newConnection, this, &Server::slotNewConnection);

    if(!myServer->listen(QHostAddress::Any, 80)){
        qDebug() << "server is not started";
    } else {
        qDebug() << "server is started";
    }
}

void Server::slotNewConnection()
{
    QTcpSocket *mySocket = myServer->nextPendingConnection();
    qDebug() << "New Connection";
    QString response = "HTTP/1.1 200 OK\r\n\r\n%1";
    mySocket->write(response.arg("Server hosted").toUtf8());

    connect(mySocket, &QTcpSocket::readyRead, this, &Server::slotServerRead);
    connect(mySocket, &QTcpSocket::disconnected, this, &Server::slotClientDisconnected);
}

void Server::slotServerRead()
{

    while(mySocket->bytesAvailable()>0)
    {
        qDebug() << "Here";
        QByteArray array = mySocket->readAll();
        QString response = "HTTP/1.1 200 OK\r\n\r\n%1";
        mySocket->write(response.arg("hi").toUtf8());
    }
}

void Server::slotClientDisconnected()
{
    mySocket->close();
    mySocket->deleteLater();
}
