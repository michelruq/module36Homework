#include <QMessageBox>

#include "startserverscreen.h"
#include "ui_startserverscreen.h"

StartServerScreen::StartServerScreen(std::shared_ptr<Database> dbPtr, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StartServerScreen)
{
    ui->setupUi(this);
    assert(dbPtr);
    m_dbPtr = dbPtr;
}

StartServerScreen::~StartServerScreen()
{
    delete ui;
}

void StartServerScreen::on_buttonBox_accepted()
{
    if(ui->passwordEdit->text().toStdString() == "skillfactory")
    {
        m_userName = QString::fromStdString("admin");
        m_userId = m_dbPtr->addUser(m_userName.toStdString(),
                                    ui->passwordEdit->text().toStdString());
        if(m_userId == -2)
        {
            QMessageBox::critical(this, tr("Error"), tr("Admin is authorized yet"));

        }
        else
        {
            accept();
        }
    }
    else
    {
        QMessageBox::critical(this, tr("Error"), tr("You can't be authorized as admin"));
    }
}


void StartServerScreen::on_buttonBox_rejected()
{
    reject();
}

QString StartServerScreen::userName() const
{
    return m_userName;
}

int StartServerScreen::userId() const
{
    return m_userId;
}

std::shared_ptr<Database> StartServerScreen::getDatabase() const
{
    return m_dbPtr;
}

