#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QString>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);

public slots:
    void slotNewConnection();
    void slotServerRead();
    void slotClientDisconnected();

private:
    QTcpServer * myServer;
    QTcpSocket * mySocket;
};

#endif // SERVER_H
