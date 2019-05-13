#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "qtdownload.h"
#include "openfile.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //Загрузка файла по ссылке
    void on_pushButtonDownload_clicked();

    //Открыть файл из папки с программой
    void on_pushButtonOpenLocalFile_clicked();

    //Открыть файл с копьютера из любой папки
    void on_pushButtonOpenGlobalFIle_clicked();

    //Cлоты смены названия таба и закрытие таба в связи с его удалением
    void setNewTabName(const QString&, const QString&);
    void closeTab(const QString&);

    //Поиск номера объекта в табах\векторе по названию файла
    int searchNameTab(const QString&);

    //Добавление нового таба (С созданием нового элемента вектора или с использованием старого)
    void addNewTab(const QString&);

    //Проверка на наличие файла в векторе/табах и вызов соотвествующей функции
    void checkOpeningFile(const QString&);

    //Закрытие таба
    void on_tabWidget_tabCloseRequested(int index);

    //Активация кнопки после окончания загрузки файла
    void enableButtonTrue();



    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
public slots:
    void sockRead();
    void sockDisc();

private:
    //Вектор с файлами которые были открыты
    QList <OpenFIle*> o;

    QtDownload dl;

    Ui::MainWindow *ui;

    QTcpSocket* socket;

    QByteArray dataFromServer;

};

#endif // MAINWINDOW_H
