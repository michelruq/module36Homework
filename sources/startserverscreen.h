#ifndef STARTSERVERSCREEN_H
#define STARTSERVERSCREEN_H

#include <QDialog>
#include <memory>
#include "Database.h"

namespace Ui {
class StartServerScreen;
}

class StartServerScreen : public QDialog
{
    Q_OBJECT

public:
    explicit StartServerScreen(std::shared_ptr<Database> dbPtr = nullptr, QWidget *parent = nullptr);
    ~StartServerScreen();

    std::shared_ptr<Database> getDatabase() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::StartServerScreen *ui;
    std::shared_ptr<Database> m_dbPtr;
};

#endif // STARTSERVERSCREEN_H
