#ifndef QTDOWNLOAD_H
#define QTDOWNLOAD_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class QtDownload : public QObject {
    Q_OBJECT
public:
    explicit QtDownload();
signals:
    void done();

private:
    QNetworkAccessManager manager;
    QString nameLocalCollection;

public slots:

    //Запуск загрузки и сохранение файла по ее завершению
    void download(const QString& url, const QString& collectionName);
    void downloadFinished(QNetworkReply* data);
};

#endif // QTDOWNLOAD_H
