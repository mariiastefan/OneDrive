#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_App.h"
#include <QPushButton>

class App : public QMainWindow
{
	Q_OBJECT

public:
	App(QWidget* parent = Q_NULLPTR);


private:
	Ui::App ui;
	bool on_search = false;
	QPushButton* newButton;


};
