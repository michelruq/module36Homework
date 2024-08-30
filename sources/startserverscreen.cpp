#include "startserverscreen.h"
#include "ui_startserverscreen.h"

StartServerScreen::StartServerScreen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StartServerScreen)
{
    ui->setupUi(this);
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

