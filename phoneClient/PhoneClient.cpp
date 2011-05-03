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

void PhoneClient::sendMsg(QString msg) {
  QTextStream cout(stdout);
  cout << "Sending message in phoneclient" << endl;

  /* Send message to server */
  sendData(2, msg);

}

void PhoneClient::getUsers() {

  /* Send message to get stringlist */
  sendData(4, "");

}

void PhoneClient::run() {


  sock->waitForConnected();
  QDataStream in(sock);

  sendData(1, nickname);


  while (true) {
    quint16 len;
    quint8 type;
    QString data;
 
    if (!sock->waitForReadyRead(60000))
      continue;
    in >> len >> type >> data;

    QTextStream cout (stdout);
    cout << type << ": " << data << endl;
    switch (type) {
      case 5: 
        emit newMsg(data);
        break;
      case 6:
        emit usersList(data.split(":"));
        break;
      }

  }

}

void PhoneClient::sendData(int type, QString msg) {

  QTextStream cout(stdout);
  cout << "sending type " << type << endl;

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
