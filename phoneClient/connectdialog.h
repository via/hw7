#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include <QDialog>

namespace Ui {
    class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDialog(QWidget *parent = 0);
    ~ConnectDialog();
	enum ScreenOrientation {
		ScreenOrientationLockPortrait,
		ScreenOrientationLockLandscape,
		ScreenOrientationAuto
	};

	void setOrientation(ScreenOrientation orientation);

private:
    Ui::ConnectDialog *ui;

signals:
    void confirm(QString, QString, QString);

private slots:
    void on_connectButton_clicked();
};

#endif // CONNECTDIALOG_H
