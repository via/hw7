#include "connectdialog.h"
#include "ui_connectdialog.h"

ConnectDialog::ConnectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectDialog)
{
    ui->setupUi(this);
}

ConnectDialog::~ConnectDialog()
{
    delete ui;
}

void ConnectDialog::on_connectButton_clicked()
{
    //connection magic
       //emit signal to thread class slot
  emit confirm(ui->ipLine->text(), ui->portLine->text(), ui->nickLine->text());
  accept();
}
