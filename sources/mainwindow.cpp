#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "startscreen.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow *MainWindow::createClient()
{
    StartScreen s;
    auto result = s.exec();
    if(result == QDialog::Rejected)
    {
        return nullptr;
    }
    auto w = new MainWindow();
    w->setAttribute(Qt::WA_DeleteOnClose);
    return w;
}


void MainWindow::on_messageLineEdit_returnPressed()
{
    on_sendMessageButton_clicked();
}


void MainWindow::on_sendMessageButton_clicked()
{

}

void MainWindow::on_privateMessageSendButton_clicked()
{

}


void MainWindow::on_actionOpen_another_client_triggered()
{
    auto w = createClient();
    if(w)
        w->show();
}


void MainWindow::on_actionClose_this_client_triggered()
{
    this -> close();
}


