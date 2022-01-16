#include "Interface.h"
#include <fstream>
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    /*AppWindow app;
    app.show();*/
    Interface interfata;
    interfata.show();
    return a.exec();
}
