#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Interface.h"

class Interface : public QMainWindow
{
    Q_OBJECT

public:
    Interface(QWidget *parent = Q_NULLPTR);

private slots:
    void on_closeBtn_clicked();

private:
    Ui::InterfaceClass ui;
};
