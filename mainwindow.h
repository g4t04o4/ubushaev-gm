#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "graphwidget.h"

#include <QMainWindow>
#include <QActionGroup>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>

class GraphWidget;

/*!
 * \brief Класс окна программы, созданный на основе QMainWindow.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    /*!
     * \brief Конструктор главного окна.
     */
    explicit MainWindow(QWidget *parent = nullptr);

private slots:

    /*!
     * \brief Действие, выполняемое по соответствующему сигналу.
     */
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

    /*!
     * \brief Виджет, содержащий сцену с графом.
     */
    GraphWidget *widget;

    /*!
     * \brief Метод, назначающий управление окном.
     */
    void createActions();

    /*!
     * \brief Метод, ответственный за отрисовку меню.
     */
    void createMenus();

    /*!
     * \brief Главные пункты меню.
     */
    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;

    /*!
     * \brief Подпункты меню.
     */
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
