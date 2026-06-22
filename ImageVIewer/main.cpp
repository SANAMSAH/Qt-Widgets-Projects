#include "ImageVIewer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setStyle("Fusion");

    QPalette darkPalette;

    darkPalette.setColor(QPalette::Window, QColor(45, 45, 48));
    darkPalette.setColor(QPalette::WindowText, Qt::white);

    darkPalette.setColor(QPalette::Base, QColor(37, 37, 38));
    darkPalette.setColor(QPalette::AlternateBase, QColor(45, 45, 48));

    darkPalette.setColor(QPalette::Text, Qt::white);

    darkPalette.setColor(QPalette::Button, QColor(45, 45, 48));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);

    darkPalette.setColor(QPalette::Highlight, QColor(0, 122, 204));
    darkPalette.setColor(QPalette::HighlightedText, Qt::white);

    app.setPalette(darkPalette);

    ImageVIewer window;
    window.show();
    return app.exec();
}
