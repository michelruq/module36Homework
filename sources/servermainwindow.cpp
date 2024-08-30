#include "servermainwindow.h"
#include "ui_servermainwindow.h"

ServerMainWindow::ServerMainWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ServerMainWindow)
{
    ui->setupUi(this);
}

ServerMainWindow::~ServerMainWindow()
{
    delete ui;
}

void ServerMainWindow::on_messageLineEdit_returnPressed()
{
    on_sendMessageButton_clicked();
}


void ServerMainWindow::on_sendMessageButton_clicked()
{

}


void ServerMainWindow::on_privateMessageSendButton_clicked()
{

}


void ServerMainWindow::on_showMessageListButton_clicked()
{

}


void ServerMainWindow::on_showUserListButton_clicked()
{

}


void ServerMainWindow::on_blockUserButton_clicked()
{

}


void ServerMainWindow::on_unblockUserButton_clicked()
{

}


void ServerMainWindow::on_deleteUserButton_clicked()
{

}

