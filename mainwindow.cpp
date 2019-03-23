#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QtNetwork/QNetworkAccessManager>
#include <QByteArray>

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

void MainWindow::on_plusButton_clicked()
{

}

