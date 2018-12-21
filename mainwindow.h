#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "graphwidget.h"

#include <QMainWindow>
#include <QActionGroup>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>

class GraphWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void openFile();
    void saveFile();
    void saveAsFile();
    void exportFile();
    void recreateGraph();
    void clearGraph();
    void shuffleGraph();
    void fillGraph();
    void zoomIn();
    void zoomOut();
    void pause();
    void about();

private:
    GraphWidget *widget;

    void createActions();
    void createMenus();

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *exportAct;
    QAction *recreateAct;
    QAction *clearAct;
    QAction *shuffleAct;
    QAction *fillAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *pauseAct;
    QAction *aboutAct;
};

#endif // MAINWINDOW_H
