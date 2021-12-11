#include "App.h"
#include <qstackedwidget.h>
#include <QVBoxLayout>
#include <qcombobox.h>
#include <QCombobox>
#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QMessageBox>
App::App(QWidget* parent)
    : QMainWindow(parent)
{

    ui.setupUi(this);
    QPixmap bg("background.jpg");
    bg = bg.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bg);
    this->setPalette(palette);
    this->setWindowIcon(QIcon("logo1.jpg"));
    this->setWindowTitle("OneDrive Search");
}



