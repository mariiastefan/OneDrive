#include "Interface.h"
#include <qstackedwidget.h>
#include <QVBoxLayout>
#include <qcombobox.h>
#include <QCombobox>
#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QMessageBox>
#include <iostream>
#include "User.h"
#include "App.h"
#include "ui_App.h"
#include "AppWindow.h"
#include "ui_AppWindow.h"
#include <fstream>
std::fstream g("conturi.txt");
Interface::Interface(QWidget* parent)
	: QMainWindow(parent)
{

	ui.setupUi(this);
	QPixmap bg("login_bg.jpg");
	bg = bg.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Background, bg);
	this->setPalette(palette);
	this->setWindowIcon(QIcon("logo1.jpg"));
	this->setWindowTitle("OneDrive");

	ui.Register->setHidden(true);

}


void Interface::on_signIn_clicked()
{
	on_signIn = true;
	bool flag = true;
	bool flag2 = true;
	bool flag3 = true;
	QString username = ui.lineEdit_username->text();
	
	std::string x = username.toStdString();
	
	/*AppWindow app;
	app.show();*/
	//this->setHidden(true);
}

void Interface::on_signUp_clicked()
{
	on_signUp = true;
	QPixmap bg("login_bg.jpg");
	QPalette palette;
	QLabel confirm_pass;
	//palette.setBrush(wdg->backgroundRole(), QBrush(QImage("logo1.jpg")));
	this->setWindowTitle("Create OneDrive Account");
	palette.setBrush(QPalette::Background, bg);

	ui.signIn->setHidden(true);
	ui.label->setHidden(true);
	ui.Register->setHidden(false);
}

void Interface::on_Register_clicked()
{
	bool verif_user = true;
	QString username = ui.lineEdit_username->text();
	User user(username.toStdString());
	/*verif_user = verify_if_user_exists(g, user);*/
	if (verif_user == true)
	{
		User newUser(username.toStdString());
		g << newUser;
	}
	
}

