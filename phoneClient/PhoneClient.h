#ifndef PHONECLIENT_H
#define PHONECLIENT_H

#include <QtGui>


class PhoneClient : public QThread {
	Q_OBJECT

	public:
    PhoneClient(QString host, QString port, QString nick, QObject *parent = 0);

	public slots:

	private:

};

#endif

