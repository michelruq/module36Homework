#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();

signals:
    void registerRequested();
    void accepted();
    void rejected();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_registerButton_clicked();

private:
    Ui::LoginForm *ui;
};

#endif // LOGINFORM_H
