#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QDialog>
#include <memory>
#include "Database.h"

namespace Ui {
class StartScreen;
}

class StartScreen : public QDialog
{
    Q_OBJECT

public:
    explicit StartScreen(std::shared_ptr<Database> dbPtr = nullptr, QWidget *parent = nullptr);
    ~StartScreen();
    void setLoginForm();
    void setRegistrationForm();

    std::shared_ptr<Database> getDatabase() const;

public slots:
    void onLoggedIn();
    void onRejectRequested();


private:
    Ui::StartScreen *ui;
    std::shared_ptr<Database> m_dbPtr;
};

#endif // STARTSCREEN_H
