#include "AppWindow.h"
#include "ui_AppWindow.h"

AppWindow::AppWindow(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::AppWindow();
	ui->setupUi(this);
}

AppWindow::~AppWindow()
{
	delete ui;
}