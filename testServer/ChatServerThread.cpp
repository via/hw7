/****************************************************
 * Group 2, ECE 3574, Spring 2011, Homework 7
 * Date: 5/6/2011
 * **************************************************/


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

/* This will be run for every connection */
void ChatServerThread::run() {

  QTextStream cout (stdout);


  sock = new QTcpSocket();
  /*Create a QTcpSocket from the descriptor */
  if (!sock->setSocketDescriptor(socket)) {
    return;
  }
  cout << "Run started" << endl;
  
  while(true) {
    QDataStream in(sock);

    quint16 length; /* These three variables will be what we receive */
    quint8 type;
    QString data;

    if (!sock->waitForReadyRead(60000))  /*Wait for data to be available */
      continue;
    in >> length >> type >> data; /* Input the data */
    QLinkedList<ChatServerThread *>::const_iterator iter;
    QLinkedList<ChatServerThread *>::iterator i;

    switch (type) {
      case 1: /* Type 1 -- New connection */
        name = new QString(data);
        cout << *name << endl;
        break;
      case 2: /* Type 2 -- iterate over all clients and send the line to it */
        for (iter = clients->constBegin(); iter != clients->constEnd(); ++iter) {
          (*iter)->addLine(5, *name + QString(": ") + data);
        }
        break;
      case 3: /* Type 3 -- find the client and remove it */
        for (i = clients->begin(); i != clients->end(); ++i) {
          if ((*i) == this) {
            i = clients->erase(i);
          }
        }
        terminate();
        break;
      case 4: /* Type 4 -- return a list of all clients */
        QStringList names;
        QLinkedList<ChatServerThread *>::const_iterator iter = clients->constBegin();
        for (iter = clients->constBegin(); iter != clients->constEnd(); ++iter) {
          names << (*iter)->getName();
        }

        addLine(6, names.join(":")); /* Bind together with colons */
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

/* General function to send back a message with a type */
void ChatServerThread::addLine(int type, QString line) {

  /* Send response */
  if (sock->isValid()) {
    QByteArray outblock;
    QDataStream out(&outblock, QIODevice::WriteOnly);
    out << (quint16)0;
    out << (quint8)type;
    out << line;
    out.device()->seek(0); /*Seek back to set the time */
    out << (quint16)(outblock.size() - sizeof(quint16));
    sock->write(outblock);
    sock->flush();

  }

}

