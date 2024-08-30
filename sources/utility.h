#ifndef UTILITY_H
#define UTILITY_H

#include <QDialog>
#include <QVBoxLayout>
#include <QListWidget>
#include <QDialogButtonBox>

class Utility
{
public:
    static int GetNameFromList (QWidget * parentPtr, std::string& name,  std::vector<string> userNameList)
    {
        QDialog dial(parentPtr);
        dial.setModal(parentPtr);
        auto l = new QVBoxLayout();
        dial.setLayout(l);
        auto userListWgt = new QListWidget(&dial);
        l->addWidget(userListWgt);
        auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dial);
        l->addWidget(buttonBox);

        QObject::connect(buttonBox, &QDialogButtonBox::accepted, &dial, &QDialog::accept);
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, &dial, &QDialog::reject);

        for(auto& user : userNameList)
        {
            userListWgt->addItem(QString::fromStdString(user));
        }

        userListWgt->setCurrentRow(0);

        auto result = dial.exec();
        bool retValue = (result == QDialog::Accepted && userListWgt->currentItem());
        if (retValue)
        {
            name = userListWgt->currentItem()->text().toStdString();
        }
        return (retValue);
    }
};

#endif // UTILITY_H
