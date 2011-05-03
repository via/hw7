#include "PhoneClient.h"
#include "ui_mainwindow.h"
#include "ui_usersdialog.h"

#include <QtCore>
#include <QtGui>

QTM_USE_NAMESPACE

PhoneClient::PhoneClient(QWidget *parent)
	: QMainWindow(parent), ui(new Ui::PhoneClient) {

	ui->setupUi(this);
	
}

void PhoneClient::usersDialogSlot() {
	UsersDialog *ud = new UsersDialog(this);
	ud->show();
}
