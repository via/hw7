
#include <QtGui>
#include "ChatServer.h"

ChatServer::ChatServer(QObject *parent) : QTcpServer(parent) {

}

void ChatServer::incomingConnection(int socket) {

  QTextStream cout(stdout);

  cout << "Connection!" << endl;

}
