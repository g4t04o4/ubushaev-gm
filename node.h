#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>

class Edge;
class GraphWidget;
class QGraphicsSceneMouseEvent;

/*
 * Элемент графа. Тоже на основе итема из QT.
 */
class Node : public QGraphicsItem
{
public:
    /*
     * Конструктор элемента графа.
     *
     * GraphWidget *graphWidget - виджет, в который будет вестись отрисовка элемента.
     * (на самом деле, немного костыль, но пока ничего лучше не придумал)
     */
    Node(GraphWidget *graphWidget);

    /*
     * Метод добавления смежного к элементу ребра в его лист.
     *
     * Edge *edge - ссылка на ребро.
     */
    void addEdge(Edge *edge);

    /*
     * Геттер на смежные элементу рёбра.
     *
     * Возвращает лист ссылок на рёбра.
     */
    QList<Edge *> getEdges() const;

    /*
     * Тип итема. И геттер для него.
     */
    enum {Type = UserType + 1};
    int type() const override {return Type;}

    /*
     * Метод для рассчёта сил, действующих на узел.
     */
    void calculeteForces();

    /*
     * Метод изменяет старую позицию узла на текущую.
     */
    bool advancePosition();

    /*
     *
     */
    QRectF boundingRect() const override;

    QPainterPath shape() const override;

    /*
     * Метод для отрисовки элемента на основе метода QPainter'а.
     *
     * QPainter *painter,
     * const QStyleOptionGraphicsItem *option - необходимые параметры для отрисовки
     * QWidget *widget - виджет, в который будет вестись отрисовка
     */
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

protected:
    /*
     *
     */
    QVariant itemChange(GraphicsItemChange change,
                        const QVariant &value) override;

    /*
     * Обработчики событий для узла.
     */

    /*
     * Обработчик нажатия на узел (левой клавишей мыши).
     * Т.н. "зажатое" состояние узла.
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    /*
     * Обработчик "отпускания" узла.
     * "Свободное" его состояние.
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QList<Edge *> edgeList; // Лист смежных узлу рёбер. Точнее, ссылок на них.
    QPointF newPos; // Актуальная позиция узла.
    GraphWidget *graph; // Виджет, в который ведётся отрисовка текущего узла.

};

#endif // NODE_H
