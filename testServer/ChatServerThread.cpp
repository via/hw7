
#include <QtGui>

#include <QLinkedList>
#include <QDataStream>
#include <QTcpSocket>
#include <QThread>

#include "ChatServerThread.h"

ChatServerThread::ChatServerThread(int socket, 
    QLinkedList<ChatServerThread *> *list, QObject *parent) : QThread(parent) {
    
  this->clients = list;
  this->socket = socket;
    
}

void ChatServerThread::run() {

  QTextStream cout (stdout);


  sock = new QTcpSocket();
  if (!sock->setSocketDescriptor(socket)) {
    return;
  }
  cout << "Run started" << endl;
  
  while(true) {
    QDataStream in(sock);

    quint16 length;
    quint8 type;
    QString data;

    if (!sock->waitForReadyRead(60000)) 
      continue;
    in >> length >> type >> data;
    cout << "received type " << type << ": " << data << endl;
    QLinkedList<ChatServerThread *>::const_iterator iter;
    QLinkedList<ChatServerThread *>::iterator i;

    switch (type) {
      case 1:
        name = new QString(data);
        cout << *name << endl;
        break;
      case 2:
        for (iter = clients->constBegin(); iter != clients->constEnd(); ++iter) {
          (*iter)->addLine(5, *name + QString(": ") + data);
        }
        break;
      case 3:
        for (i = clients->begin(); i != clients->end(); ++i) {
          if ((*i) == this) {
            i = clients->erase(i);
          }
        }
        terminate();
        break;
      case 4:
        QStringList names;
        QLinkedList<ChatServerThread *>::const_iterator iter = clients->constBegin();
        for (iter = clients->constBegin(); iter != clients->constEnd(); ++iter) {
          names << (*iter)->getName();
        }

        addLine(6, names.join(":"));
        /* Get names and send them */
        break;
      }
  }
}


QString ChatServerThread::getName() {

  if (name)
    return *name;

  return QString("[not connected]");
}

void ChatServerThread::addLine(int type, QString line) {

  /* Send response */
  if (sock->isValid()) {
    QByteArray outblock;
    QDataStream out(&outblock, QIODevice::WriteOnly);
    out << (quint16)0;
    out << (quint8)type;
    out << line;
    out.device()->seek(0);
    out << (quint16)(outblock.size() - sizeof(quint16));
    sock->write(outblock);
    sock->flush();

  }

}

