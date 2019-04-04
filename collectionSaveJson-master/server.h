#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QString>
#include <QMap>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0,quint16 port = 6000,QString nameHost = "Host",QMap<QString,QString> collection_ = {});
    ~Server();
public slots:
    void slotNewConnection();
    void slotServerRead();
    void slotClientDisconnected();


private:
    QTcpServer * myServer;
    QTcpSocket * mySocket;
    QString name;
    QMap <QString,QString> collection;
};

#endif // SERVER_H
