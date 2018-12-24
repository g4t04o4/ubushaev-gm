#include "graphwidget.h"
#include "edge.h"
#include "node.h"
#include "exporter.h"
#include "importer.h"

#include <math.h>

#include <QKeyEvent>
#include <QRandomGenerator>
#include <QList>
#include "edgedata.h"

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent), lastNodeID(0), timerId(0), nodeCount(35),
      edgeCount(50), wsize(600), pauseflag(false)
{
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-wsize / 2, -wsize / 2, wsize, wsize);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(wsize, wsize);


    leaderNode = new Node(this, lastNodeID++);
    scene->addItem(leaderNode);
    nodeHeap.append(leaderNode);
    leaderNode->setPos(0, 0);

    fillGraph(nodeCount, edgeCount);
}

void GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
}

void GraphWidget::openGraphFromTXT(QString inpFile)
{
    clearScreen();
    Importer inpMaster;
    QVector<EdgeData *> edgeDataHeap = QVector<EdgeData *>();
    nodeCount = static_cast<int>(inpMaster.importFromTXT(edgeDataHeap, inpFile));

    for (int i = 0; i < nodeCount; i++)
    {
        Node *newNode = new Node(this, lastNodeID++);
        nodeHeap.append(newNode);
        scene->addItem(newNode);
        newNode->setPos(-wsize / 2 + QRandomGenerator::global()->bounded(wsize),
                        -wsize / 2 + QRandomGenerator::global()->bounded(wsize));
    }
    edgeCount = edgeDataHeap.count();
    for (int i = 0; i < edgeCount; i++)
    {
        EdgeData data = *(edgeDataHeap.at(i));
        Edge *newEdge = new Edge(nodeHeap.at(static_cast<int>(data.src)),
                                 nodeHeap.at(static_cast<int>(data.dest)));
        scene->addItem(newEdge);
        edgeHeap.append(newEdge);
    }

    for (auto* item: edgeDataHeap)
    {
        delete item;
    }
}

void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Up:
        leaderNode->moveBy(0, -20);
        break;
    case Qt::Key_Down:
        leaderNode->moveBy(0, 20);
        break;
    case Qt::Key_Left:
        leaderNode->moveBy(-20, 0);
        break;
    case Qt::Key_Right:
        leaderNode->moveBy(20, 0);
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void GraphWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    if (!pauseflag)
    {
        foreach (Node *node, nodeHeap)
            node->calculeteForces();

        bool itemsMoved = false;
        foreach (Node *node, nodeHeap)
        {
            if (node->advancePosition())
                itemsMoved = true;
        }

        if (!itemsMoved)
        {
            killTimer(timerId);
            timerId = 0;
        }
    }
}

void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow(2.0, -event->delta() / 240.0));
}

void GraphWidget::drawBackground(QPainter *painter,
                                 const QRectF &rect)
{
    Q_UNUSED(rect);

    /*
     * Тень.
     */

    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(),
                       sceneRect.top() + 5,
                       5,
                       sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5,
                        sceneRect.bottom(),
                        sceneRect.width(),
                        5);
    if (rightShadow.intersects(rect)
            || rightShadow.contains(rect))
        painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect)
            || bottomShadow.contains(rect))
        painter->fillRect(bottomShadow, Qt::darkGray);

    /*
     * Заполнение.
     */

    QLinearGradient gradient(sceneRect.topLeft(),
                             sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);
}

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform()
            .scale(scaleFactor, scaleFactor)
            .mapRect(QRectF(0, 0, 1, 1))
            .width();
    if (factor < 0.07 || factor > 100) return;

    scale(scaleFactor, scaleFactor);
}

void GraphWidget::shuffle()
{
    foreach (QGraphicsItem *item, scene->items())
    {
        if (qgraphicsitem_cast<Node *>(item))
            item->setPos(-wsize / 2 + QRandomGenerator::global()->bounded(wsize),
                         -wsize / 2 + QRandomGenerator::global()->bounded(wsize));
    }
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

void GraphWidget::pause()
{
    pauseflag = !pauseflag;
}

void GraphWidget::exportToPNG(QString filename)
{
    QPixmap pixMap = this->grab();
    Exporter expMaster;
    expMaster.exportToPNG(&pixMap, filename);
}

void GraphWidget::recreate()
{
    this->clearScreen();
    this->fillGraph(nodeCount, edgeCount);
}

void GraphWidget::clearScreen()
{
    foreach (QGraphicsItem *item, scene->items())
    {
        delete item;
    }
    nodeHeap.clear();
    edgeHeap.clear();
    lastNodeID = 0;
}

void GraphWidget::fillGraph(int nodeCount, int edgeCount)
{
    for (int i = 0; i < nodeCount; i++)
    {
        Node *newNode = new Node(this, lastNodeID++);
        nodeHeap.append(newNode);
        scene->addItem(newNode);
        newNode->setPos(-wsize / 2 + QRandomGenerator::global()->bounded(wsize),
                        -wsize / 2 + QRandomGenerator::global()->bounded(wsize));
    }

    for (int i = 0; i < edgeCount; i++)
    {
        Edge *newEdge = new Edge(nodeHeap.at(QRandomGenerator::global()->bounded(nodeCount-1)),
                                 nodeHeap.at(QRandomGenerator::global()->bounded(nodeCount-1)));
        scene->addItem(newEdge);
        edgeHeap.append(newEdge);
    }
}

void GraphWidget::exportToTXT(QString filename)
{
    /* JSON (TODO){
     * edgeCnt: 42,
     * nodeCnt: 42,
     * nodes:
     * [
     * {
     * src:1,
     * dest:2
     * },
     * {
     * src:1,
     * dest:2
     * }
     * ]
     * }
     */
    /*
     * 42
     * 41
     * 1 2
     * 2 1
     *
     */



    QString report;
    report.append(QString::number(nodeCount));
    report.append("\r\n");
    report.append(QString::number(edgeCount));
    foreach (Edge *edge, edgeHeap)
    {
        report.append("\r\n");
        report.append(QString::number(edge->getDestNode()->getID()));
        report.append(" ");
        report.append(QString::number(edge->getSourceNode()->getID()));
    }
    Exporter expMaster;
    expMaster.exportToTXT(report, filename);
}
