#include "graphwidget.h"
#include "mainwindow.h"

#include <QApplication>
#include <QTime>
#include <QMainWindow>
#include <QDesktopWidget>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MainWindow mainWindow;

    mainWindow.show();
    return app.exec();
}
