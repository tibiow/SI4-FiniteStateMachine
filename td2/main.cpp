#include "domo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Domo w;
    w.show();

    return a.exec();
}


