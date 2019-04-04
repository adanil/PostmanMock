#ifndef OPENFILE_H
#define OPENFILE_H

#include <QDialog>
#include <QFile>
#include "qtdownload.h"

namespace Ui {
class OpenFIle;
}

class OpenFIle : public QDialog
{
    Q_OBJECT

public:
    explicit OpenFIle(QString collectionName, QWidget *parent = nullptr);
    ~OpenFIle();
    QString getCollectionName() { return collectionName; }

    //закрытие файла при закрытии таба
    void closeCollectionFile();
    QString getFullFillePath();

signals:

    //Сигналы смены имени файла и его удалении
    void changeName(const QString&, const QString&);
    void close(const QString&);

private slots:
    //Кнопки смены имени, удаления и обновления по ссылке файла
    void on_pushButtonSetNameCollection_clicked();
    void on_pushButtonDeleteCollection_clicked();
    void on_pushButtonUpDateCollection_clicked();

    //Показ json в виде текста при запуске/обновлении файла
    void showCollection();

    //Открытие файла после его обновления
    void downloadEnd();


private:
    Ui::OpenFIle *ui;

    //Cкачивание файла
    QtDownload dl;

    //Открытый файл
    QFile* collection = nullptr;

    //Адрес этого файла БЕЗ приписки ".json"
    QString collectionName;

};

#endif // OPENFILE_H
