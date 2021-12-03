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
	ui.label_confirmpass->setHidden(true);
	ui.lineEdit_confirmpass->setHidden(true);
	ui.Register->setHidden(true);
	//connect(ui.theme, QOverload<int>(&QComboBox::activated), this, &Interface::changeTheme);
   /* QWidget* firstPageWidget = new QWidget;
	QWidget* secondPageWidget = new QWidget;
	QWidget* thirdPageWidget = new QWidget;

	QStackedWidget *stackedWidget = new QStackedWidget;
	stackedWidget->addWidget(firstPageWidget);
	stackedWidget->addWidget(secondPageWidget);
	stackedWidget->addWidget(thirdPageWidget);*/

	/*  QVBoxLayout* layout = new QVBoxLayout;
	  layout->addWidget(stackedWidget);
	  setLayout(layout);
	  QComboBox *pageComboBox = new QComboBox;
	  pageComboBox->addItem(tr("Page 1"));
	  pageComboBox->addItem(tr("Page 2"));
	  pageComboBox->addItem(tr("Page 3"));
	  connect(pageComboBox, QOverload<int>::of(&QComboBox::activated),
	  stackedWidget, &QStackedWidget::setCurrentIndex);*/
}


void Interface::on_signIn_clicked()
{
	on_signIn = true;
	bool flag = true;
	bool flag2 = true;
	bool flag3 = true;
	QString username = ui.lineEdit_username->text();
	QString password = ui.lineEdit_password->text();
	std::string x = username.toStdString();
	std::string y = password.toStdString();
	
	
	/*if (flag == false)
	{
		QMessageBox msgBox;
		msgBox.setText("Sign In Failed");
		msgBox.setInformativeText("Wrong Password");
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.exec();
	}
	if (flag2 == false)
	{
		QMessageBox msgBox;
		msgBox.setText("Sign In Failed");
		msgBox.setInformativeText("This username does not exist");
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.exec();
	}
	if (flag3 == false)
	{
		QMessageBox msgBox;
		msgBox.setText("Sign In Failed");
		msgBox.setBaseSize(QSize(800, 300));
		msgBox.setInformativeText("Passwords don't coincide");
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.exec();
	}*/
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
	ui.label_confirmpass->setHidden(false);
	ui.lineEdit_confirmpass->setHidden(false);
	ui.signIn->setHidden(true);
	ui.label->setHidden(true);
	ui.Register->setHidden(false);
}

void Interface::on_Register_clicked()
{
	QString username = ui.lineEdit_username->text();
	QString password = ui.lineEdit_password->text();
	QString confirm_password = ui.lineEdit_confirmpass->text();
	User user(username.toStdString(), password.toStdString());
	if (verify_pass(password.toStdString()) == false)
	{
		QMessageBox msgBox;
		msgBox.setText("Sign Up Failed");
		msgBox.setInformativeText("Password does not contain all the characters");
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.exec();

	}
	// de facut ce e comentat
	/*if (password == confirm_password) {
		User newU(username.toStdString(), password.toStdString());
		std::cout << newU;
	}
	else {
		QMessageBox msgBox;
		msgBox.setText("Sign In Failed");
		msgBox.setInformativeText("This username does not exist");
		msgBox.setStandardButtons(QMessageBox::Ok);
		msgBox.exec();
	}*/
}

