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
//#include "AppWindow.h"
#include <fstream>
#include "Client.h"


std::fstream g("conturi.txt", std::ios::app);
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
	ui.Back->setHidden(true);
	ui.Register->setHidden(true);

}


void Interface::on_signIn_clicked()
{
	on_signIn = true;

	QString username = ui.lineEdit_username->text();

	std::string x = username.toStdString();
	g.open("conturi.txt");
	g.close();
	bool verif_user = false;
	User user(x);
	verif_user = user.verify_if_user_exists(g);
	if (verif_user == true)
	{
		Client client;
		client.connect();
		QMessageBox msgBox;
		msgBox.setText("corect !");
		msgBox.exec();
		hide();
		homePage = new App(user, this);
		homePage->show();
	}
	else {
		QMessageBox msgBox;
		msgBox.setText("Username does not exist !");
		msgBox.exec();
	}

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

	ui.Back->setHidden(false);
	ui.signIn->setHidden(true);
	ui.label->setHidden(true);
	ui.Register->setHidden(false);
}

void Interface::on_Register_clicked()
{
	g.open("conturi.txt");
	g.close();
	bool verif_user = true;
	const QString username = ui.lineEdit_username->text();
	User user(username.toStdString());
	verif_user = user.verify_if_user_exists(g);
	if (verif_user == false)
	{
		g.open("conturi.txt", std::ios::app);
		User newUser(username.toStdString());
		g << newUser;
		g.close();
	}
	else {
		QMessageBox msgBox;
		msgBox.setText("Username already exists !");
		msgBox.exec();
	}
	
}

void Interface::on_Back_clicked()
{
	ui.Back->setHidden(true);
	ui.signIn->setHidden(false);
	ui.label->setHidden(false);
	ui.Register->setHidden(true);
}

