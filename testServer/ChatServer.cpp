
#include <QtGui>
#include <QTcpServer>
#include <QLinkedList>
#include "ChatServer.h"
#include "ChatServerThread.h"

ChatServer::ChatServer(QObject *parent) : QTcpServer(parent) {
  clients = new QLinkedList<ChatServerThread *>();

}

void ChatServer::incomingConnection(int socket) {

  QTextStream cout(stdout);
  cout << "Connection!" << endl;

  ChatServerThread *newclient = new ChatServerThread(socket, clients);
  newclient->start();
  clients->append(newclient);



}
