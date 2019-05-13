 #include "qtdownload.h"
#include <QNetworkRequest>
#include <QFile>
#include <QJsonDocument>
#include <QMessageBox>
#include "server.h"
#include "mainwindow.h"
#include <QApplication>
#include "server.h"
#include <QtCore/QDebug>
#include <QtCore/QJsonDocument>
#include <QtCore/QCoreApplication>
#include <QMap>

// Network
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

QtDownload::QtDownload() : QObject()
{
    QObject::connect(&manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(downloadFinished(QNetworkReply*)));    
}

void QtDownload::downloadFinished(QNetworkReply *data)
{
    QFile localFile(nameLocalCollection);

    if (!localFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox info("Внимание", "Загрузка прошла неудачно, либо неудалось открыть файл.",
                                                         QMessageBox::Information,
                                                         QMessageBox::Ok,
                                                         QMessageBox::NoButton,
                                                         QMessageBox::Escape);
        info.exec();
        return;
    }

    QByteArray responseData = data->readAll();
    QJsonDocument doc( QJsonDocument::fromJson(responseData));
    QString strJson(doc.toJson(QJsonDocument::Compact));

    QTextStream out(&localFile);
    out << strJson;

    localFile.close();

    QMessageBox info("Внимание", "Загрузка завершена.",
                                                     QMessageBox::Information,
                                                     QMessageBox::Ok,
                                                     QMessageBox::NoButton,
                                                     QMessageBox::Escape);

    info.exec();

    emit done();
}

void QtDownload::download(const QString& InUrl, const QString& nameLocalCollection)
{
    this->nameLocalCollection = nameLocalCollection;
    QUrl url = QUrl::fromEncoded(InUrl.toLocal8Bit());
    manager.get(QNetworkRequest(url));
}

