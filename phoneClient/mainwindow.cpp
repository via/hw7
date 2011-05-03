// checksum 0xa193 version 0x30001
/*
  This file was generated by the Mobile Qt Application wizard of Qt Creator.
  MainWindow is a convenience class containing mobile device specific code
  such as screen orientation handling.
  It is recommended not to modify this file, since newer versions of Qt Creator
  may offer an updated version of it.
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore/QCoreApplication>

#include "connectdialog.h"
#include "usersdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	usersAction = new QAction("Users", this);
	quitAction = new QAction("Quit", this);
	connect(quitAction, SIGNAL(triggered()), this, SLOT(endProgram()));
  connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(newMessageOut()));
	QMenu *menu = new QMenu("Fremantle", this);
	menu->addAction(usersAction);
	menu->addAction(quitAction);
	menuBar()->addMenu(menu);

	ConnectDialog *connector = new ConnectDialog();
  connect(connector, SIGNAL(confirm(QString, QString, QString)),
      this, SLOT(setup(QString, QString, QString)));
	connector->setOrientation(ConnectDialog::ScreenOrientationAuto);
	connector->show();

  client = NULL;

}

void MainWindow::newMessageIn(QString line) {
  ui->chatTextEdit->appendPlainText(line);
}

void MainWindow::newMessageOut() {

  QTextStream cout(stdout);
  QString message = ui->lineEdit->text();
  cout << ui->lineEdit->text() << endl;
  cout << "Sending message in mainwindow: " << message << endl;
  ui->lineEdit->clear();

  client->sendMsg(message);
}


void MainWindow::newUsersList(QStringList users) {

  UsersDialog *dia = new UsersDialog(users, this);
  dia->show();
}

void MainWindow::endProgram() {
  client->disconnect(); 	
  close(); 
}

void MainWindow::setup(QString host, QString port, QString nick) {

  QTextStream cout(stdout);
  client = new PhoneClient(host, port, nick, NULL);
	connect(usersAction, SIGNAL(triggered()), client, SLOT(getUsers()));
  connect(client, SIGNAL(usersList(QStringList)), this, SLOT(newUsersList(QStringList)));
  connect(client, SIGNAL(newMsg(QString)), this, SLOT(newMessageIn(QString)));
  cout << "Called connect" << endl;
  client->connect();
  client->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setOrientation(ScreenOrientation orientation)
{
#if defined(Q_OS_SYMBIAN)
    // If the version of Qt on the device is < 4.7.2, that attribute won't work
    if (orientation != ScreenOrientationAuto) {
        const QStringList v = QString::fromAscii(qVersion()).split(QLatin1Char('.'));
        if (v.count() == 3 && (v.at(0).toInt() << 16 | v.at(1).toInt() << 8 | v.at(2).toInt()) < 0x040702) {
            qWarning("Screen orientation locking only supported with Qt 4.7.2 and above");
            return;
        }
    }
#endif // Q_OS_SYMBIAN

    Qt::WidgetAttribute attribute;
    switch (orientation) {
#if QT_VERSION < 0x040702
    // Qt < 4.7.2 does not yet have the Qt::WA_*Orientation attributes
    case ScreenOrientationLockPortrait:
        attribute = static_cast<Qt::WidgetAttribute>(128);
        break;
    case ScreenOrientationLockLandscape:
        attribute = static_cast<Qt::WidgetAttribute>(129);
        break;
    default:
    case ScreenOrientationAuto:
        attribute = static_cast<Qt::WidgetAttribute>(130);
        break;
#else // QT_VERSION < 0x040702
    case ScreenOrientationLockPortrait:
        attribute = Qt::WA_LockPortraitOrientation;
        break;
    case ScreenOrientationLockLandscape:
        attribute = Qt::WA_LockLandscapeOrientation;
        break;
    default:
    case ScreenOrientationAuto:
        attribute = Qt::WA_AutoOrientation;
        break;
#endif // QT_VERSION < 0x040702
    };
    setAttribute(attribute, true);
}

void MainWindow::showExpanded()
{
#ifdef Q_OS_SYMBIAN
    showFullScreen();
#elif defined(Q_WS_MAEMO_5) || defined(Q_WS_MAEMO_6)
    showMaximized();
#else
    show();
#endif
}
