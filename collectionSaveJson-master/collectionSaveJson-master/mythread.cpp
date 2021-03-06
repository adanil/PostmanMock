#include "mythread.h"

MyThread::MyThread(qintptr ID,QMap<QString,QVariant> collection_, QObject *parent) :
    QThread(parent)
{
    collection = collection_;
    this->socketDescriptor = ID;
}

void MyThread::run()
{
    // thread starts here
    qDebug() << " Thread started";

    socket = new QTcpSocket();

    // set the ID
    if(!socket->setSocketDescriptor(this->socketDescriptor))
    {
        // something's wrong, we just emit a signal
        emit error(socket->error());
        return;
    }

    // connect socket and signal
    // note - Qt::DirectConnection is used because it's multithreaded
    //        This makes the slot to be invoked immediately, when the signal is emitted.

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

    // We'll have multiple clients, we want to know which is which
    qDebug() << socketDescriptor << " Client connected";
    socket->write("Hekllpo");

    // make this thread a loop,
    // thread will stay alive so that signal/slot to function properly
    // not dropped out in the middle when thread dies

    exec();
}

void MyThread::readyRead()
{
    QByteArray array = socket->readAll();
    qDebug() << array;
    QString s = "";
    QString arrS = (QString)array;
    for (int i = 0;i <arrS.size()-2;i++)
        s.append(arrS[i]);
    qDebug() << "Request: " << s << " Answer: " << collection[s].toString().toUtf8();
    socket->write(collection[s].toString().toUtf8());
}

void MyThread::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";


    socket->deleteLater();
    exit(0);
}
