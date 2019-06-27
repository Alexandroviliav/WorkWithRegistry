#include "mainwindow.h"
#include "ui_mainwindow.h"
//"C:\Windows\System32\notepad.exe"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Работа с реестром");
    settings =  new QSettings("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",QSettings::NativeFormat);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    // Сздать папку
    settings->beginGroup("Run");

    // Запись в реестр
    QString string;
    string = {"\"C:\\Windows\\System32\\notepad.exe\""};
    QVariant var(string);
    settings->setValue("Notepad",string);

    // Закрыть папку
    settings->endGroup();

    // Синхронизация реестра
    settings->sync();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->textEdit->clear();
    QStringList keyList = settings->allKeys();
    QStringList valueList;
    for(int i = 0; i < keyList.size(); ++i)
    {
        valueList.push_back(settings->value(keyList.at(i)).toString());
        ui->textEdit->insertPlainText("Ключ: \t" + keyList.at(i) + "\n");
        ui->textEdit->insertPlainText("Значение: \t" + valueList.at(i) + "\n");
    }
}
