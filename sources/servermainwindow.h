#ifndef SERVERMAINWINDOW_H
#define SERVERMAINWINDOW_H

#include <QDialog>
#include <memory>
#include "Database.h"

namespace Ui {
class ServerMainWindow;
}

class ServerMainWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ServerMainWindow(
                              std::shared_ptr<Database> dbPtr = nullptr,
                              QWidget *parent = nullptr);
    ~ServerMainWindow();

private slots:
    void on_messageLineEdit_returnPressed();

    void on_sendMessageButton_clicked();

    void on_privateMessageSendButton_clicked();

    void on_showMessageListButton_clicked();

    void on_showUserListButton_clicked();

    void on_blockUserButton_clicked();

    void on_unblockUserButton_clicked();

    void on_deleteUserButton_clicked();

private:
    Ui::ServerMainWindow *ui;
    std::shared_ptr<Database> m_dbPtr;
};

#endif // SERVERMAINWINDOW_H
