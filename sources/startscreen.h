#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QDialog>

namespace Ui {
class StartScreen;
}

class StartScreen : public QDialog
{
    Q_OBJECT

public:
    explicit StartScreen(QWidget *parent = nullptr);
    ~StartScreen();

    void setLoginForm();
    void setRegistrationForm();

public slots:
    void onLoggedIn();
    void onRejectRequested();


private:
    Ui::StartScreen *ui;
};

#endif // STARTSCREEN_H
