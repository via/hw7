#include "mainwindow.h"
#include "usersdialog.h"
#include "ui_usersdialog.h"

UsersDialog::UsersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UsersDialog)
{
    ui->setupUi(this);

}

/* Constructor to create the user list dialog */
UsersDialog::UsersDialog(QStringList qsl, QWidget *parent) :
  QDialog(parent), ui(new Ui::UsersDialog)
{
    ui->setupUi(this);
    for(int i=0;i<qsl.size();i++)
    {
        ui->listWidget->addItem(qsl.value(i));
    }
}

UsersDialog::~UsersDialog()
{
    delete ui;
}
