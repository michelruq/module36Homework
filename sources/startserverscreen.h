#ifndef STARTSERVERSCREEN_H
#define STARTSERVERSCREEN_H

#include <QDialog>

namespace Ui {
class StartServerScreen;
}

class StartServerScreen : public QDialog
{
    Q_OBJECT

public:
    explicit StartServerScreen(QWidget *parent = nullptr);
    ~StartServerScreen();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::StartServerScreen *ui;
};

#endif // STARTSERVERSCREEN_H
