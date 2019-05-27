#include "additem.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    addItem w;
    w.show();

    return a.exec();
}
