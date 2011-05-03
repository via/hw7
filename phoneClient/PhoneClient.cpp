#include "PhoneClient.h"
#include "ui_mainwindow.h"
#include "ui_usersdialog.h"

#include <QtCore>
#include <QTcpSocket>
#include <QtGui>


PhoneClient::PhoneClient(QString host, QString port,
    QString nick, QObject *parent)
	: QThread(parent) {

    nickname = nick;
    hostname = host;
    this->port = port.toInt();

    sock = new QTcpSocket();
	
}

void PhoneClient::connect() {

  sock->connectToHost(hostname, port);

  /* Send connect message */

}

void PhoneClient::sendMsg(QString) {

  /* Send message to server */

}

void PhoneClient::getUsers() {

  /* Send message to get stringlist */

}

void PhoneClient::run() {

  while (true) {;}

}

