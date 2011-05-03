
#include <QCoreApplication>

#include "ChatServer.h"

int main(int argc, char **argv) {


  QCoreApplication app(argc, argv);

  ChatServer cs;
  cs.listen(QHostAddress::Any, 5155);

  return app.exec();

}
