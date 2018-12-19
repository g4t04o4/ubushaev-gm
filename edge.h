#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

class Node;

/*!
 * \brief Ребро графа. Сделано на основе QTшного QGraphicsItem.
 */

class Edge : public QGraphicsItem
{
public:
    /**
     * \brief Конструктор ребра на основе двух элементов.
     * \param sourceNode ссылка на начальный элемент
     * \param destNode ссылка на конечный элемент
     */
    Edge(Node *sourceNode, Node *destNode);

    /*!
     * Геттер для получения начального элемента.
     *
     * Возвращает ссылку на элемент.
     */
    Node *getSourceNode() const;

    /*!
     * Геттер для получения конечного элемента.
     *
     * Возвращает ссылку на элемент.
     */
    Node *getDestNode() const;

    /*!
     * Метод регулировки для ребра. Следит, чтобы ребро отрисовывалось от текущего положения элементов.
     */
    void adjust();

    /*
     * Тип итема (ребро или элемент?) и геттер для его получения.
     */
    enum {Type = UserType + 2};
    int type() const override { return Type; }

protected:
    /*
     *
     */
    QRectF boundingRect() const override;

    /*
     * Метод для отрисовки ребра на основе метода QPainter'а.
     *
     * QPainter *painter,
     * const QStyleOptionGraphicsItem *option - необходимые параметры для отрисовки
     * QWidget *widget - виджет, в который будет вестись отрисовка
     */
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

private:
    Node *source, * dest; // Ребро хранит в себе ссылки на его элементы.

    QPointF sourcePoint; // Координаты начального элемента ребра.
    QPointF destPoint; // Координаты конечного элемента ребра.
    qreal arrowSize; // Размер указателя стрелки при отрисовке.
};

#endif // EDGE_H
