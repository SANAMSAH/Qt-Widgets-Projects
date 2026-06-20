#include "PaintApp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    PaintApp window;
    window.show();
    return app.exec();
}
