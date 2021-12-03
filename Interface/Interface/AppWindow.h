#pragma once

#include <QWidget>
namespace Ui { class AppWindow; };

class AppWindow : public QWidget
{
	Q_OBJECT

public:
	AppWindow(QWidget *parent = Q_NULLPTR);
	~AppWindow();

private:
	Ui::AppWindow *ui;
};
