#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Interface.h"

class Interface : public QMainWindow
{
	Q_OBJECT

public:
	Interface(QWidget* parent = Q_NULLPTR);

private slots:
	void on_signIn_clicked();
	void on_signUp_clicked();

private:
	Ui::InterfaceClass ui;
	bool on_signIn = false;
	bool on_signUp = false;

};
