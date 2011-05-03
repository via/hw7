#ifndef USERSDIALOG_H
#define USERSDIALOG_H

#include <QDialog>
#include <QStringList>

namespace Ui {
    class UsersDialog;
}

class UsersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UsersDialog(QWidget *parent = 0);
    UsersDialog(QStringList qsl);
    ~UsersDialog();

private:
    Ui::UsersDialog *ui;
};

#endif // USERSDIALOG_H
