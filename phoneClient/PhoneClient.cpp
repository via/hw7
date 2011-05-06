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

/*Send message back to server */
void PhoneClient::sendMsg(QString msg) {
  QTextStream cout(stdout);
  cout << "Sending message in phoneclient" << endl;

  /* Send message to server */
  sendData(2, msg);

}

/* Slot for sending disconnect message */
void PhoneClient::disconnect() {
        sendData(3, "");
}

void PhoneClient::getUsers() {

  /* Send message to get stringlist */
  sendData(4, "");

}

void PhoneClient::run() {


  sock->waitForConnected();
  QDataStream in(sock);

  /* Send initial connect message */
  sendData(1, nickname);


  while (true) {
    quint16 len;
    quint8 type; /* receiving into these vars */
    QString data;
 
    if (!sock->waitForReadyRead(60000)) /*Wait until input is ready */
      continue;
    in >> len >> type >> data; /*Input*/

    QTextStream cout (stdout);
    cout << type << ": " << data << endl;
    switch (type) {
      case 5: 
        emit newMsg(data); /* new message received */
        break;
      case 6:
        emit usersList(data.split(":")); /* Returned message containing user list */
        break;
      }

  }

}

/* Generic function to send data of type type. */
void PhoneClient::sendData(int type, QString msg) {

  QTextStream cout(stdout);
  cout << "sending type " << type << ": " << msg << endl;

  QByteArray block;
  QDataStream out(&block, QIODevice::WriteOnly);
  out << (quint16)0;
  out << (quint8)type;
  out << msg;
  out.device()->seek(0);
  out << (quint16)(block.size() - sizeof(quint16));
  sock->write(block);
  sock->flush();

}
