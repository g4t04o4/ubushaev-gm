#include "mainwindow.h"
#include "graphwidget.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QKeySequence>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle(tr("FDL"));

    widget  = new GraphWidget;
    setCentralWidget(widget);

    createActions();
    createMenus();
}

void MainWindow::createActions()
{

    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcut(QKeySequence("Ctrl+O"));
    openAct->setStatusTip(tr("Open a file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(openFile()));

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcut(QKeySequence("Ctrl+S"));
    saveAct->setStatusTip(tr("Save a file"));
    connect(saveAct, SIGNAL(triggered()), this, SLOT(saveFile()));

    saveAsAct = new QAction(tr("Save &As"), this);
    saveAsAct->setShortcut(QKeySequence("Ctrl+Shift+S"));
    saveAsAct->setStatusTip(tr("Save a file as something"));
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAsFile()));

    exportAct = new QAction(tr("&Export"), this);
    exportAct->setShortcut(QKeySequence("Ctrl+E"));
    exportAct->setStatusTip(tr("Export a file"));
    connect(exportAct, SIGNAL(triggered()), this, SLOT(exportFile()));

    recreateAct = new QAction(tr("&Recreate"), this);
    recreateAct->setShortcut(QKeySequence("Ctrl+R"));
    recreateAct->setStatusTip(tr("Recreate graph"));
    connect(recreateAct, SIGNAL(triggered()), this, SLOT(recreateGraph()));

    clearAct = new QAction(tr("&Clear"), this);
    clearAct->setShortcut(QKeySequence("Ctrl+C"));
    clearAct->setStatusTip(tr("Clear graph"));
    connect(clearAct, SIGNAL(triggered()), this, SLOT(clearGraph()));

    shuffleAct = new QAction(tr("&Shuffle"), this);
    shuffleAct->setShortcut(QKeySequence("Ctrl+Q"));
    shuffleAct->setStatusTip(tr("Shuffle graph"));
    connect(shuffleAct, SIGNAL(triggered()), this, SLOT(shuffleGraph()));

    fillAct = new QAction(tr("&Fill"), this);
    fillAct->setShortcut(QKeySequence("Ctrl+F"));
    fillAct->setStatusTip(tr("Fill graph"));
    connect(fillAct, SIGNAL(triggered()), this, SLOT(fillGraph()));

    zoomInAct = new QAction(tr("&ZoomIn"), this);
    zoomInAct->setShortcut(QKeySequence("-"));
    zoomInAct->setStatusTip(tr("Zoom In"));
    connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));

    zoomOutAct = new QAction(tr("&ZoomOut"), this);
    zoomOutAct->setShortcut(QKeySequence("+"));
    zoomOutAct->setStatusTip(tr("Zoom Out"));
    connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));

    pauseAct = new QAction(tr("&Pause"), this);
    pauseAct->setShortcut(QKeySequence("P"));
    pauseAct->setStatusTip(tr("Pause"));
    connect(pauseAct, SIGNAL(triggered()), this, SLOT(pause()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setShortcut(QKeySequence("F1"));
    aboutAct->setStatusTip(tr("About"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exportAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(recreateAct);
    editMenu->addAction(clearAct);
    editMenu->addAction(shuffleAct);
    editMenu->addAction(fillAct);

    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(zoomInAct);
    viewMenu->addAction(zoomOutAct);
    viewMenu->addSeparator();
    viewMenu->addAction(pauseAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}

void MainWindow::openFile()
{
    QString fileContent = QFileDialog::getOpenFileName(this);
    widget->openGraphFromTXT(fileContent);
}

void MainWindow::saveFile()
{
    saveAsFile();
}

void MainWindow::saveAsFile()
{
    QString filename = QFileDialog::getSaveFileName(this);
    widget->exportToTXT(filename);
}

void MainWindow::exportFile()
{
    QString filename = QFileDialog::getSaveFileName(this);
    widget->exportToPNG(filename);
}

void MainWindow::recreateGraph()
{
    widget->recreate();
}

void MainWindow::clearGraph()
{
    widget->clearScreen();
}

void MainWindow::shuffleGraph()
{
    widget->shuffle();
}

void MainWindow::fillGraph()
{
    widget->fillGraph(32, 50);
}

void MainWindow::zoomIn()
{
    widget->zoomIn();
}

void MainWindow::zoomOut()
{
    widget->zoomOut();
}

void MainWindow::pause()
{
    widget->pause();
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About"),
                       tr("Программа даёт вам уникальную возможность потыкать кривой граф!\r\n"
                          "Более того, вы можете сохранить этот ужас в PNG формате, распечатать и вложить в кошелёк, "
                          "чтобы хвастаться на корпоративах перед коллегами!\r\n"
                          "Будьте уверены, они страшно обзавидуются!"));
}
