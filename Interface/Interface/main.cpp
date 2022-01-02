#include "Interface.h"
#include <fstream>
#include <QtWidgets/QApplication>
//#include "AppWindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    /*AppWindow app;
    app.show();*/
    Interface interface;
    interface.show();
    return a.exec();
}
