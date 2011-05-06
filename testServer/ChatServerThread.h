/****************************************************
 * Group 2, ECE 3574, Spring 2011, Homework 7
 * Date: 5/6/2011
 * **************************************************/


#ifndef CHATSERVERTHREAD_H
#define CHATSERVERTHREAD_H

#include <QObject>
#include <QThread>

#include <QLinkedList>
#include <QTcpSocket>


class ChatServerThread : public QThread {
  Q_OBJECT

  public:
    ChatServerThread(int socket, QLinkedList<ChatServerThread *> *list, QObject *parent = 0);
    void run();
    QString getName();

  public slots:
    void addLine(int, QString);


  private:
    QString *name;
    QTcpSocket *sock;
    int socket;
    QLinkedList<ChatServerThread *> *clients;
};
  


#endif

