#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_App.h"
#include <QPushButton>

class App : public QMainWindow
{
	Q_OBJECT

public:
	App(QWidget* parent = Q_NULLPTR);
private slots:
	void on_addNew_clicked();
	void on_new_folder_clicked();
	//void on_new_file_clicked();
private:
	Ui::App ui;
	bool on_addNew = false;
	QPushButton* newButton;


};
