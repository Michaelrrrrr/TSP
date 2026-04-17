#include "TSP.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    TSP window;
    window.show();
    return app.exec();
}
