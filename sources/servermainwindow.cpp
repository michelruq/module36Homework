#include "servermainwindow.h"
#include "ui_servermainwindow.h"

ServerMainWindow::ServerMainWindow(int userId,
                                   QString userName,
                                   std::shared_ptr<Database> dbPtr,
                                   QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ServerMainWindow),
    m_userId(userId),
    m_userName(userName)
{
    ui->setupUi(this);
    assert(dbPtr);
    m_dbPtr = dbPtr;
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

