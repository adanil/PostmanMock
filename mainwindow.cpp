#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QByteArray>
#include "server.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_createBut_clicked()
{
    QString name = ui->nameEdit->text();
    int port = ui->portEdit->text().toInt();
}
