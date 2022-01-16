#include "Interface.h"
#include <fstream>
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Interface interface;
    interface.show();
    return a.exec();
}
