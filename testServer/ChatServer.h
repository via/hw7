
#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QLinkedList>
#include "QServerThread.h"

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
  
