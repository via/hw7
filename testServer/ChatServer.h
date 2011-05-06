/****************************************************
 * Group 2, ECE 3574, Spring 2011, Homework 7
 * Date: 5/6/2011
 * **************************************************/


#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QLinkedList>
#include "ChatServerThread.h"

class ChatServer : public QTcpServer {
  Q_OBJECT

  public:
    ChatServer(QObject *parent = 0);

  protected:
    void incomingConnection(int socket);

  private:
    QLinkedList<ChatServerThread *> *clients;

};

#endif
  
