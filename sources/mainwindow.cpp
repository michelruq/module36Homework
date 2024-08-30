#include <QTimer>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "startscreen.h"
#include "startserverscreen.h"
#include "utility.h"

MainWindow::MainWindow(int userId,
                       QString userName,
                       std::shared_ptr<Database> dbPtr,
                       QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_userId(userId),
    m_userName(userName)
{
    ui->setupUi(this);
    assert(dbPtr);
    m_dbPtr = dbPtr;

    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateChats);
    timer->start(10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow *MainWindow::createClient(std::shared_ptr<Database> dbPtr)
{
    StartScreen s(dbPtr);
    auto result = s.exec();
    if(result == QDialog::Rejected)
    {
        return nullptr;
    }
    auto w = new MainWindow(s.userId(), s.userName(), s.getDatabase());
    w->setAttribute(Qt::WA_DeleteOnClose);
    return w;
}

ServerMainWindow *MainWindow::createServerClient(std::shared_ptr<Database> dbPtr)
{
    assert(dbPtr);
    StartServerScreen s(dbPtr);
    auto result = s.exec();
    if(result == QDialog::Rejected)
    {
        return nullptr;
    }
    auto sw = new ServerMainWindow(s.userId(), s.userName(), s.getDatabase());
    return sw;
}


void MainWindow::on_messageLineEdit_returnPressed()
{
    on_sendMessageButton_clicked();
}


void MainWindow::on_sendMessageButton_clicked()
{
    m_dbPtr->addChatMessage(m_userName.toStdString(),
                            ui->messageLineEdit->text().toStdString());
}


void MainWindow::on_privateMessageSendButton_clicked()
{
    std::string destinationName;

    if(Utility::GetNameFromList(this, destinationName, m_dbPtr->getUserList()))
    {
        m_dbPtr->addPrivateMessage(m_userName.toStdString(),
                                   destinationName,
                                   ui->messageLineEdit->text().toStdString());
    }
}


void MainWindow::on_actionOpen_another_client_triggered()
{
    auto w = createClient(m_dbPtr);
    if(w)
        w->show();
}


void MainWindow::on_actionClose_this_client_triggered()
{
    this -> close();
}

void MainWindow::updateChats()
{
    auto chatMessages = m_dbPtr->getChatMessages();
    QString chat;
    for(const auto &msg : chatMessages)
    {
        chat.append(QString::fromStdString(msg) + "\n");
    }
    if(ui->commonChatBrowser->toPlainText() != chat)
    {
        ui->commonChatBrowser->setText(chat);
    }

    chat.clear();

    auto privateMessages = m_dbPtr->getPrivateMessage();
    for(const auto &msg : privateMessages)
    {
        if(QString::fromStdString(msg.getSender()) != m_userName && msg.getDest() != m_userId)
        {
            continue;
        }
        QString prefix;
        if(m_userName == QString::fromStdString(msg.getSender()) &&
            m_userId == msg.getDest())
        {
            prefix = tr("self message") + ": ";
        }
        else if(m_userName == QString::fromStdString(msg.getSender()))
        {
            prefix = tr("message to") +
                     QString(" <%1>: ").
                     arg(QString::fromStdString(m_dbPtr->getUserName(msg.getDest())));
        }
        else
        {
            prefix = "<" + QString::fromStdString(msg.getSender()) +
                     "> " + tr("say to you") + ": ";
        }
        chat.append(prefix + QString::fromStdString(msg.getText()) + "\n");
    }
    if(ui->commonChatBrowser->toPlainText() != chat)
    {
        ui->privateChatBrowser->setText(chat);
    }

}


void MainWindow::on_actionOpen_server_client_triggered()
{
    auto w = createServerClient(m_dbPtr);
    if(w)
        w->show();
}

