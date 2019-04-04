#include "server.h"
#include <QDebug>
#include <QCoreApplication>
#include <QString>
Server::Server(QObject *parent,quint16 port,QString nameHost,QMap<QString,QString> collection_) : QObject(parent)
{
    myServer = new QTcpServer(this);
    name = nameHost;
    collection = collection_;

        connect(myServer, &QTcpServer::newConnection, this, &Server::slotNewConnection);

        if(!myServer->listen(QHostAddress::Any, port)){
            qDebug() << "server is not started";
        } else {
            qDebug() << "server is started";
        }
    }
Server::~Server(){
    qDebug() << "Server closed";
}
    void Server::slotNewConnection()
    {
        qDebug() << "New connetction";
        mySocket = myServer->nextPendingConnection();
        QString hello = "Server hosted by " + name;
        mySocket->write(hello.toUtf8());

        connect(mySocket, &QTcpSocket::readyRead, this, &Server::slotServerRead);
        connect(mySocket, &QTcpSocket::disconnected, this, &Server::slotClientDisconnected);
    }

    void Server::slotServerRead()
    {
        while(mySocket->bytesAvailable()>0)
        {
            qDebug() << "New request";
            QByteArray array = mySocket->readAll();
            QString s = "";
            QString arrS = (QString)array;
            for (int i = 0;i <arrS.size()-2;i++)
                s.append(arrS[i]);
            qDebug() << "Request: " << s << " Answer: " << collection[s].toUtf8();
            mySocket->write(collection[s].toUtf8());
        }
    }

    void Server::slotClientDisconnected()
    {
        mySocket->close();
        mySocket->deleteLater();
    }

