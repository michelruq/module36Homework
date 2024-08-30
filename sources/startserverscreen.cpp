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
    accept();
}


void StartServerScreen::on_buttonBox_rejected()
{
    reject();
}

std::shared_ptr<Database> StartServerScreen::getDatabase() const
{
    return m_dbPtr;
}

