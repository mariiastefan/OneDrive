#include "Interface.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Interface w;
    Interface w;
    w.show();
 
    return a.exec();
}
