/****************************************************
 * Group 2, ECE 3574, Spring 2011, Homework 7
 * Date: 5/6/2011
 * **************************************************/


#include <QCoreApplication>

#include "ChatServer.h"

int main(int argc, char **argv) {


  QCoreApplication app(argc, argv);

  ChatServer cs;
  cs.listen(QHostAddress::Any, 5155);

  return app.exec();

}
