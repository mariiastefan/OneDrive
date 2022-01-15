#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_App.h"
#include <QPushButton>
#include <QFileSystemModel>
#include "User.h"

class App : public QMainWindow
{
	Q_OBJECT

public:
	App(QWidget* parent = Q_NULLPTR);
	App(const User& x, QWidget* parent = Q_NULLPTR);
private slots:
	//void on_new_folder_clicked();
	void on_add_clicked();
	void on_deleteBtn_clicked();
	void on_searchBtn_clicked();
	void on_Back_clicked();
	//void on_treeView_clicked(QModelIndex index);

private:
	Ui::App ui;
	bool Search = false;
	QPushButton* newButton;
	/*QFileSystemModel* dirModel;
	QFileSystemModel* fileModel;*/
	QFileSystemModel* model;
	std::string UserName;
};
