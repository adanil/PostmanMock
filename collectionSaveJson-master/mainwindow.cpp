#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>
#include <QByteArray>
#include <QTabBar>
#include <QFileDialog>
#include "server.h"
QString name;
int port;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Postman mock");
    ui->tabWidget->setTabText(0, "Скачать коллекцию");
    ui->tabWidget->setTabText(1, "Открыть коллекцию");
    ui->lineEditNameCollection->setPlaceholderText("Введите имя коллекции");
    ui->lineEditCollectionOpenName->setPlaceholderText("Введите имя коллекции");
    ui->lineEditURL->setPlaceholderText("https://www.getpostman.com/collections/807270dbc2fbf5b2d9fc");

    QTabBar *tabBar = ui->tabWidget->tabBar();
    tabBar->tabButton(0, QTabBar::RightSide)->hide();
    tabBar->tabButton(1, QTabBar::RightSide)->hide();
}

MainWindow::~MainWindow()
{    
    for(const auto& i : o) delete i;

    delete ui;
}

void MainWindow::on_pushButtonOpenLocalFile_clicked()
{
    checkOpeningFile(ui->lineEditCollectionOpenName->text() + ".json");
}

void MainWindow::on_pushButtonOpenGlobalFIle_clicked()
{
    QString fileUrl = QFileDialog::getOpenFileName(nullptr, "Выберите коллекцию", "", "*.json");

    checkOpeningFile(fileUrl);
}

void MainWindow::checkOpeningFile(const QString& fileUrl)
{
    QFileInfo openFile(fileUrl);
    if (searchNameTab(openFile.absoluteFilePath()) == -1)
    {
        addNewTab(openFile.absoluteFilePath());
    }
    else
    {
        QMessageBox info("Внимание", "Файл который вы пытаетесь открыть уже открыт.",
                                                         QMessageBox::Information,
                                                         QMessageBox::Ok,
                                                         QMessageBox::NoButton,
                                                         QMessageBox::Escape);
        info.exec();
    }
}

void MainWindow::addNewTab(const QString& nameFile)
{
    QFile collection(nameFile);
    if (!collection.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox info("Внимание", "Файл который вы пытаетесь открыть не существует или расположен в другой папке.",
                                                         QMessageBox::Information,
                                                         QMessageBox::Ok,
                                                         QMessageBox::NoButton,
                                                         QMessageBox::Escape);
        info.exec();
        return ;
    }
    collection.close();

    o += new OpenFIle(nameFile);

    ui->tabWidget->addTab(o.last(), nameFile.right(nameFile.length() - nameFile.lastIndexOf("/") - 1));

    connect(o.last(), SIGNAL(changeName(const QString&, const QString&)), this, SLOT(setNewTabName(const QString&, const QString&)));
    connect(o.last(), SIGNAL(close(const QString&)), this, SLOT(closeTab(const QString&)));
}

int MainWindow::searchNameTab(const QString& tabName)
{
    for(auto i =0; i<o.length(); i++){
        if (o[i]->getFullFillePath() == tabName) {
            return i;
        }
    }
    return -1;
}

void MainWindow::closeTab(const QString& tabName)
{
    int indexTab = searchNameTab(tabName);

    ui->tabWidget->removeTab(indexTab+2);

    int indexList = indexTab;

    delete o[indexList];

    o.erase(o.begin()+indexList);

}

void MainWindow::setNewTabName(const QString& oldNameTab, const QString& newTabName)
{
    int numTub = searchNameTab(oldNameTab) + 2;
    ui->tabWidget->setTabText(numTub, newTabName + ".json");
}

void MainWindow::on_pushButtonDownload_clicked()
{
    QFile checkFile(ui->lineEditNameCollection->text()+".json");
    if (checkFile.exists()){
        qDebug() << "fiel exists" << "\n";
        QMessageBox* yesOrNo =  new QMessageBox("Выберите действие",
                            "Данный файл уже существует, перезаписать его?",
                            QMessageBox::Information,
                            QMessageBox::Yes,
                            QMessageBox::No,
                            QMessageBox::Escape);
        int n = yesOrNo->exec();
        delete yesOrNo;

        //user clicked Yes
        if (n != 3)  return;
    }
    checkFile.close();

    ui->pushButtonDownload->setEnabled(false);

    connect(&dl, SIGNAL(done()),this, SLOT(enableButtonTrue()));
    dl.download(ui->lineEditURL->text(), ui->lineEditNameCollection->text() + ".json");
}

void MainWindow::enableButtonTrue()
{
    ui->pushButtonDownload->setEnabled(true);
}

void MainWindow::on_tabWidget_tabCloseRequested(int indexTab)
{
    ui->tabWidget->removeTab(indexTab);

    int indexList = indexTab - 2;

    delete o[indexList];

    o.erase(o.begin()+indexList);
}
