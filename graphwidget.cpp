#include "graphwidget.h"
#include "edge.h"
#include "node.h"

#include <math.h>

#include <QKeyEvent>
#include <QRandomGenerator>
#include <QList>
#include <QPixmap>
#include <QFile>
#include <QTextStream>

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent), timerId(0), nodeCount(35),
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
    setWindowTitle(tr("ForceDirectedLayout"));



    leaderNode = new Node(this);
    scene->addItem(leaderNode);
    leaderNode->setPos(0, 0);


    for (int i = 0; i < nodeCount; i++)
    {
        Node *newNode = new Node(this);
        nodeHeap.insert(i, newNode);
        scene->addItem(newNode);
        newNode->setPos(-wsize / 2 + QRandomGenerator::global()->bounded(wsize),
                        -wsize / 2 + QRandomGenerator::global()->bounded(wsize));
    }

    for (int i = 0; i < edgeCount; i++)
    {
        scene->addItem(new Edge(nodeHeap.at(QRandomGenerator::global()->bounded(nodeCount-1)),
                                nodeHeap.at(QRandomGenerator::global()->bounded(nodeCount-1))));
    }
}

void GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
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
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
        shuffle();
        break;
    case Qt::Key_P:
        pause();
        break;
    case Qt::Key_S:
        exportToPNG();
       break;
    case Qt::Key_R:
        recreate();
        break;
    case Qt::Key_C:
        clearScreen();
        break;
    case Qt::Key_T:
        exportToText();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void GraphWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QList<Node *> nodes;
    foreach (QGraphicsItem *item, scene->items())
    {
        if (Node *node = qgraphicsitem_cast<Node *> (item))
            nodes << node;
    }

    if (!pauseflag)
    {
    foreach (Node *node, nodes)
        node->calculeteForces();

    bool itemsMoved = false;
    foreach (Node *node, nodes)
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

    /*
     * Кайнда туториал.
     */

    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
                    sceneRect.width() - 4, sceneRect.height() - 4);
    QString message(tr("shuffle - Space, zoomIn - +, zoomOut - -, pause - P, exportToPNG - S, exportToText - T, clearScreen - C, recreate - R"));

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(14);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    painter->drawText(textRect.translated(2, 2), message);
    painter->setPen(Qt::black);
    painter->drawText(textRect, message);
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

void GraphWidget::exportToPNG()
{
    QPixmap pixMap = this->grab();
    pixMap.save("export_report.png");
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
}

void GraphWidget::fillGraph(int nodeCount, int edgeCount)
{
    for (int i = 0; i < nodeCount; i++)
    {
        Node *newNode = new Node(this);
        nodeHeap.insert(i, newNode);
        scene->addItem(newNode);
        newNode->setPos(-wsize / 2 + QRandomGenerator::global()->bounded(wsize),
                        -wsize / 2 + QRandomGenerator::global()->bounded(wsize));
    }

    for (int i = 0; i < edgeCount; i++)
    {
        scene->addItem(new Edge(nodeHeap.at(QRandomGenerator::global()->bounded(nodeCount-1)),
                                nodeHeap.at(QRandomGenerator::global()->bounded(nodeCount-1))));
    }
}

void GraphWidget::exportToText()
{
    QString report;
    int nodeCnt = 1, edgeCnt = 1;

    foreach (QGraphicsItem *item, scene->items())
    {

        if (Node *node = qgraphicsitem_cast<Node *> (item))
        {
            report.append("node_");
            report.append(QString::number(nodeCnt));
            report.append("\r\n");
            nodeCnt++;
        }
        else
        {
            /*
             * Пока покатит. Потом заменить.
             */
            report.append("edge_");
            report.append(QString::number(edgeCnt));
            report.append("\r\n");
            edgeCnt++;
        }
    }

    QFile file("export_report.txt");
    file.resize(0);
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream << report << endl;
    }
}
