#pragma once

#include <QWidget>
#include "ui_App.h"

class App : public QWidget
{
	Q_OBJECT

public:
	App(QWidget *parent = Q_NULLPTR);
	~App();

private:
	Ui::App ui;
};
