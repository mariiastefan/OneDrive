#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Interface.h"
#include "App.h"
#include <QPushButton>

class Interface : public QMainWindow
{
	Q_OBJECT

public:
	Interface(QWidget* parent = Q_NULLPTR);

private slots:
	void on_signIn_clicked();
	void on_signUp_clicked();
	void on_Register_clicked();
	void on_Back_clicked();
	void on_delete_account_clicked();

private:
	Ui::InterfaceClass ui;
	bool on_signIn = false;
	bool on_signUp = false;
	bool on_delete_account = false;
	App *homePage;
};
