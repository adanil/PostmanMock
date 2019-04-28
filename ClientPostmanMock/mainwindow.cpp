#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(sockRead()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(sockDisc()));
    qDebug() << "Created" << endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    socket->connectToHost("192.168.0.103",6000);

}
void MainWindow::sockRead(){
    if (socket->waitForConnected(500)){
        socket->waitForReadyRead(500);
        dataFromServer = socket->readAll();
        qDebug() << dataFromServer;
    }
}

void MainWindow::sockDisc(){
    socket->deleteLater();
}

void MainWindow::on_pushButton_2_clicked()
{
 socket->write("hello");
}
