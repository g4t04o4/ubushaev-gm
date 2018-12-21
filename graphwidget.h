#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H



#include <QGraphicsView>

class Node;
class Edge;
class Exporter;

/*
 * Виджет на основе QTшного QGraphicsView, содержащий граф.
 */
class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    /*
     * Конструктор виджета.
     */
    GraphWidget(QWidget *parent = nullptr);

    void itemMoved();

public slots:
    void fillGraph(int nodeCount, int edgeCount);
    /*
     * Метод для перетасовки наугад элементов графа.
     */
    void shuffle();
    /*
     * Методы для масштабирования модели на экране.
     */
    void zoomIn();
    void zoomOut();

    void setNodeCount(int N) {nodeCount = N;}
    void setEdgeCount(int N) {edgeCount = N;}

    void pause();
    void exportToPNG(QString filename);
    void exportToTXT(QString filename);

    void clearScreen();
    void recreate();
protected:
    /*
     * Обработчики событий.
     */
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    /*
     * Отрисовка фона виджета.
     */
    void drawBackground(QPainter *painter,
                        const QRectF &rect) override;
    void scaleView(qreal scaleFactor);

private:
    unsigned int lastNodeID;
    QGraphicsScene *scene = new QGraphicsScene(this);
    QVector<Node *> nodeHeap;
    QVector<Edge *> edgeHeap;
    int timerId; //
    int nodeCount, edgeCount;
    Node *leaderNode; // Главный узел графа. Именно он двигается с помощью клавиатуры.
    int wsize; //size of widget
    bool pauseflag;

    Exporter *expMaster;
};

#endif // GRAPHWIDGET_H
