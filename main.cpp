#include "graphwidget.h"

#include <QApplication>
#include <QTime>
#include <QMainWindow>
#include <QDesktopWidget>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    GraphWidget *widget = new GraphWidget;


    QMainWindow mainWindow;
    mainWindow.setCentralWidget(widget);

    mainWindow.show();
    return app.exec();
}
