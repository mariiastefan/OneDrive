#pragma once

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QMessageBox>
#include <iostream>
#include <qstackedwidget.h>
#include <QVBoxLayout>
#include <qcombobox.h>
#include <QCombobox>
#include "User.h"
#include "FolderUser.h"
#include "ui_AppWindow.h"

namespace Ui { class AppWindow; };

class AppWindow : public QWidget
{
	Q_OBJECT
private slots:
	void on_search_clicked();
public:
	AppWindow(QWidget *parent = Q_NULLPTR);
	~AppWindow();

private:
	Ui::AppWindow *ui;
};
