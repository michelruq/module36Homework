#include <QMessageBox>

#include "servermainwindow.h"
#include "ui_servermainwindow.h"
#include "utility.h"

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
    m_dbPtr->addChatMessage(m_userName.toStdString(),
                            ui->messageLineEdit->text().toStdString());
}


void ServerMainWindow::on_privateMessageSendButton_clicked()
{
    std::string destinationName;

    if(Utility::GetNameFromList(this, destinationName, m_dbPtr->getUserList()))
    {
        m_dbPtr->addPrivateMessage(m_userName.toStdString(),
                                   destinationName,
                                   ui->messageLineEdit->text().toStdString());
    }
}


void ServerMainWindow::on_showMessageListButton_clicked()
{
    auto chatMessages = m_dbPtr->getChatMessages();
    QString chat;
    for(const auto &msg : chatMessages)
    {
        chat.append(QString::fromStdString(msg) + "\n");
    }

    auto privateMessages = m_dbPtr->getPrivateMessage();
    for(const auto &msg : privateMessages)
    {
        chat.append("<" + QString::fromStdString(msg.getSender()) + "> " + tr("say to ")
                    + QString::fromStdString(m_dbPtr->getUserName(msg.getDest())) + ": "
                    + QString::fromStdString(msg.getText()) + "\n");
    }

    if(ui->commonChatBrowser->toPlainText() != chat)
    {
        ui->commonChatBrowser->setText(chat);
    }

}


void ServerMainWindow::on_showUserListButton_clicked()
{
    auto userList = m_dbPtr->getUserList();
    QString userString;
    for(auto& user : userList)
    {
        userString.append(QString::fromStdString(user) + "\n");
    }
    if(ui->userListBrowser->toPlainText() != userString)
    {
        ui->userListBrowser->setText(userString);
    }
}


void ServerMainWindow::on_blockUserButton_clicked()
{
    std::string blockedName;

    if(Utility::GetNameFromList(this, blockedName, m_dbPtr->getUserListAvailiableForBlocking()))
    {
        string tempString = "The user <" + blockedName + ">" + " will be blocked";
        const char* temp = tempString.c_str();
        QMessageBox::critical(this, "Error", tr(temp));
        m_dbPtr->blockUser(blockedName);
    }
}


void ServerMainWindow::on_unblockUserButton_clicked()
{
    std::string unblockedName;

    if(Utility::GetNameFromList(this, unblockedName, m_dbPtr->getBlockedUserList()))
    {
        string tempString = "The user <" + unblockedName + ">" + " will be unblocked";
        const char* temp = tempString.c_str();
        QMessageBox::critical(this, "Error", tr(temp));
        m_dbPtr->unblockUser(unblockedName);
    }
}


void ServerMainWindow::on_deleteUserButton_clicked()
{

}

