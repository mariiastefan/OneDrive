#include "Interface.h"

Interface::Interface(QWidget *parent)
    : QMainWindow(parent)
{

    ui.setupUi(this);
    QPixmap bg("background.jpg");
    bg = bg.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bg);
    this->setPalette(palette);
}


void Interface::on_closeBtn_clicked()
{
    close();
}
