#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>

class Edge;
class GraphWidget;
class QGraphicsSceneMouseEvent;

/*!
 * \brief Класс, реализующий элемент графа. Наследуется от QGraphicsItem.
 */
class Node : public QGraphicsItem
{
public:

    /*!
     * \brief Конструктор элемента графа.
     * \param graphWidget - виджет, в который будет вестись отрисовка элемента.
     * \param nodeID - уникальный номер элемента.
     */
    Node(GraphWidget *graphWidget, unsigned int nodeID);

    /*!
     * \brief Метод добавления смежного к элементу ребра в его лист.
     * \param edge - ссылка на ребро.
     */
    void addEdge(Edge *edge);

    /*!
     * \brief Метод получения смежных элементу рёбер.
     * \return возвращает лист ссылок на рёбра.
     */
    QList<Edge *> getEdges() const;

    /*!
     * \brief Метод для получения уникального номера элемента.
     * \return возвращает уникальный номер элемента.
     */
    unsigned int getID() const;

    /*!
     * \brief Метод для рассчёта сил, действующих на узлы.
     */
    void calculeteForces();

    /*!
     * \brief Метод обновляет позицию элемента.
     */
    bool advancePosition();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;

    /*!
     * \brief Метод для отрисовки элемента на основе метода QPainter'а.
     */
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

protected:
    QVariant itemChange(GraphicsItemChange change,
                        const QVariant &value) override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    /*!
     * \brief Уникальный номер элемента.
     */
    unsigned int nodeID;

    /*!
     * \brief Лист ссылок на смежные узлу рёбра.
     */
    QList<Edge *> edgeList;

    /*!
     * \brief Актуальная позиция узла.
     */
    QPointF newPos;

    /*!
     * \brief Виджет, в который отрисовывается элемент.
     */
    GraphWidget *graph;

};

#endif // NODE_H
