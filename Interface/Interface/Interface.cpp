#include "Interface.h"

Interface::Interface(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void Interface::on_closeBtn_clicked()
{
    close();
}
