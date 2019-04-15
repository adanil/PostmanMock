#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QString>
#include <QMap>
#include <QVariant>
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0,quint16 port = 6000,QString nameHost = "Host",QMap<QString,QVariant> collection_ = {});
    ~Server();
public slots:
    void slotNewConnection();
    void slotServerRead();
    void slotClientDisconnected();


private:
    QTcpServer * myServer;
    QTcpSocket * mySocket;
    QString name;
    QMap <QString,QVariant> collection;
};

#endif // SERVER_H
