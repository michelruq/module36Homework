#include <QMessageBox>

#include "registrationform.h"
#include "ui_registrationform.h"

RegistrationForm::RegistrationForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RegistrationForm)
{
    ui->setupUi(this);
}

RegistrationForm::~RegistrationForm()
{
    delete ui;
}

void RegistrationForm::setDatabase(std::shared_ptr<Database> dbPtr)
{
    m_dbPtr = dbPtr;
}

void RegistrationForm::on_loginButton_clicked()
{
   emit loginRequested();
}


void RegistrationForm::on_buttonBox_accepted()
{
    if(ui->PasswordEdit->text() != ui->ConfirmationPasswordEdit->text())
    {
        QMessageBox::critical(this, tr("Error"), tr("Passwords doesn't match"));
        return;
    }
    auto userId = m_dbPtr->addUser(ui->LoginEdit->text().toStdString(),
                                   ui->PasswordEdit->text().toStdString());
    switch(userId)
    {
        case -1:
           QMessageBox::critical(this, tr("Error"), tr("Login isn't correct"));
        break;
        case -2:
            QMessageBox::critical(this, tr("Error"), tr("Login is already exist"));
        break;
        default:
            emit accepted(userId, ui->LoginEdit->text());
        break;
    }
}


void RegistrationForm::on_buttonBox_rejected()
{
    emit rejected();
}

