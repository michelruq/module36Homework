﻿#include <iostream>
#include "CommandLineInterface.h"
#include <QApplication>

#include "mainwindow.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto w = MainWindow::createClient();
    if(w)
        w->show();
    else
        return 0;
    return a.exec();
}


