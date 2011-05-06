
#include <QtGui>
#include <QTcpServer>
#include <QLinkedList>
#include "ChatServer.h"
#include "ChatServerThread.h"

ChatServer::ChatServer(QObject *parent) : QTcpServer(parent) {
  clients = new QLinkedList<ChatServerThread *>();

}


/* Called when the TcpServer gets a new connection */

void ChatServer::incomingConnection(int socket) {

  QTextStream cout(stdout);
  cout << "Connection!" << endl;

  /* Start a new server thread */
  ChatServerThread *newclient = new ChatServerThread(socket, clients);
  newclient->start();
  clients->append(newclient);



}
