#include "openfile.h"
#include "ui_openfile.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QFileInfo>
#include "server.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QByteArray>
#include <QApplication>
#include <QtCore/QDebug>
#include <QtCore/QJsonDocument>
#include <QtCore/QCoreApplication>
#include <QMap>
#include <QJsonObject>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include "mythread.h"
bool flag=0;
OpenFIle::OpenFIle(QString collectionName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenFIle)
{
    ui->setupUi(this);
    ui->portedit->setMinimum(0);
    ui->portedit->setMaximum(100000);
    ui->portedit->setValue(6001);
    ui->label->setText("Открыта коллеция: " + collectionName);

    if (flag)
    {
        ui->acceptsettingsbtn->hide();
        ui->portedit->hide();
        ui->label_2->hide();
        ui->nameedit->hide();
    }
    this->collectionName = collectionName;
    collection = new QFile(collectionName);
    if (!collection->open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox info("Внимание", "Файл не открыт.",
                                                   QMessageBox::Information,
                                                   QMessageBox::Ok,
                                                   QMessageBox::NoButton,
                                                   QMessageBox::Escape);
        info.exec();
        QWidget::close();
    }

    showCollection();
}

OpenFIle::~OpenFIle()
{
    collection->close();

    delete collection;
    delete ui;
}

QString OpenFIle::getFullFillePath()
{
    QFileInfo a(*collection);
    return a.absoluteFilePath();
}

void OpenFIle::closeCollectionFile()
{
    collection->close();
}

void OpenFIle::showCollection()
{
    QByteArray collectByte = collection->readAll();
    QString strCollection(QString::fromUtf8(collectByte));

    ui->textBrowserCollection->setText(collectByte.data());
}

void OpenFIle::on_pushButtonSetNameCollection_clicked()
{
    QString newName = QInputDialog::getText(nullptr,"Введите новое имя файла", "Имя: ");

    if (newName == "") return;

    emit changeName(getFullFillePath(), newName);

    newName.push_front(collectionName.left(collectionName.lastIndexOf("/")+1));
    newName += ".json";
    collectionName = newName;

    collection->rename(collectionName);

    ui->label->setText("Открыта коллеция: " + collectionName);
}

void OpenFIle::on_pushButtonDeleteCollection_clicked()
{
    collection->remove();
    emit close(getFullFillePath());
}

void OpenFIle::on_pushButtonUpDateCollection_clicked()
{
    QString url = QInputDialog::getText(nullptr,"Введите ccылку для обновления", "Url: ");

    if (url == "") return;

    collection->remove();
    delete collection;

    dl.download(url, collectionName);

    connect(&dl, SIGNAL(done()),this, SLOT(downloadEnd()));
}

void OpenFIle::downloadEnd()
{
    collection = new QFile(collectionName);
    collection->open(QIODevice::ReadWrite | QIODevice::Text);

    showCollection();
}

void OpenFIle::on_Requestbtn_clicked()
{/*
    QString request=ui->textBrowserRequest->toPlainText();//Это запрос куда пихать хз
    QString answer;//Это ответ который должен выдвать сервер(просто присвой этой переменной ответ)
    ui->textBrowserAnswer->setText(answer);*/
}

void OpenFIle::on_acceptsettingsbtn_clicked()
{
    ui->acceptsettingsbtn->hide();
    ui->nameedit->hide();
    ui->portedit->hide();
    QJsonDocument Doc;
    Doc=QJsonDocument::fromJson(ui->textBrowserCollection->toPlainText().toUtf8());
    QVariantMap result = Doc.object().toVariantMap();
    int port = ui->portedit->value();
    QString name;
    name=ui->nameedit->text();
    MyServer Qwe;
    Qwe.startServer(port,result);
    flag=1;
}
