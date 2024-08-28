#include "loginform.h"
#include "ui_loginform.h"

LoginForm::LoginForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginForm)
{
    ui->setupUi(this);
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::setDatabase(std::shared_ptr<Database> dbPtr)
{
    m_dbPtr = dbPtr;
}


void LoginForm::on_buttonBox_accepted()
{
    emit accepted();
}


void LoginForm::on_buttonBox_rejected()
{
    emit rejected();
}


void LoginForm::on_registerButton_clicked()
{
    emit registerRequested();
}

