#include "PhoneClient.h"
#include "ui_mainwindow.h"
#include "ui_usersdialog.h"

#include <QtCore>
#include <QtGui>


PhoneClient::PhoneClient(QString host, QString port,
    QString nick, QObject *parent)
	: QThread(parent) {

	
}

