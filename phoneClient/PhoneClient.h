/****************************************************
 * Group 2, ECE 3574, Spring 2011, Homework 7
 * Date: 5/6/2011
 * **************************************************/

#ifndef PHONECLIENT_H
#define PHONECLIENT_H

#include <QtGui>


#include <QTcpSocket>

class PhoneClient : public QThread {
	Q_OBJECT

	public:
    PhoneClient(QString host, QString port, QString nick, QObject *parent = 0);
    void run();

	public slots:
    void connect();
    void sendMsg(QString);
    void getUsers();
	void disconnect();

  signals:
    void newMsg(QString);
    void usersList(QStringList);
    

	private:
    QString nickname;
    QString hostname;
    quint16 port;
    QTcpSocket *sock;

    void sendData(int, QString);

};

#endif

