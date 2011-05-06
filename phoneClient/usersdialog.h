/****************************************************
 * Group 2, ECE 3574, Spring 2011, Homework 7
 * Date: 5/6/2011
 * **************************************************/

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
    UsersDialog(QStringList qsl, QWidget *parent = 0);
    ~UsersDialog();

private:
    Ui::UsersDialog *ui;
};

#endif // USERSDIALOG_H
