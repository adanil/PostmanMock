
#include "mainwindow.h"
#include <QApplication>

#include <QtCore/QDebug>
#include <QtCore/QJsonDocument>
#include <QtCore/QCoreApplication>

// Network
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    auto manager = new QNetworkAccessManager();
        QObject::connect(
                    manager,
                    &QNetworkAccessManager::finished,
                    // Лямбда функция - обработчик HTTP ответа
                    [=](QNetworkReply *reply) {




            // Тело ответа в формате JSON
            QByteArray responseData = reply->readAll();
            qDebug() << QJsonDocument::fromJson(responseData);

            // Delete garbage && Exit
            reply->deleteLater();
            manager->deleteLater();
            exit(0);
        });

        manager->get(QNetworkRequest(QUrl("https://www.getpostman.com/collections/0402e1a2d9ec61301fa5")));

    w.show();

    return a.exec();
}
