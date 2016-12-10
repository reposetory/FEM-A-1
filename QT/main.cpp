#include "heat_equation.h"
#include <QApplication>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    heat_equation w;

    w.show();

    a.exec();
    return 0;
}
