#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>

class Node;

/*!
 * \brief Класс, реализующий ребро графа. Наследуется от QGraphicsItem.
 */
class Edge : public QGraphicsItem
{
public:
    /*!
     * \brief Конструктор ребра на основе двух элементов.
     * \param sourceNode - начальный элемент ребра.
     * \param destNode - конечный элемент ребра.
     */
    Edge(Node *sourceNode, Node *destNode);

    /*!
     * \brief Геттер для получения начального элемента.
     * \return начальный элемент ребра.
     */
    Node *getSourceNode() const {return source;}

    /*!
     * \brief Геттер для получения конечного элемента.
     * \return конечный элемент ребра.
     */
    Node *getDestNode() const {return dest;}

    /*!
     * \brief Метод, отвечающий за корректный рассчёт и отрисовку рёбер от текущего положения элементов.
     */
    void adjust();

protected:    
    QRectF boundingRect() const override;

    /*!
     * \brief Метод для отрисовки ребра на основе метода QPainter'а.
     */
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

private:
    /*!
     * \brief Ребро хранит в себе ссылки на его элементы.
     */
    Node *source, * dest;
    /*!
     * \brief Координаты начального элемента ребра.
     */
    QPointF sourcePoint;
    /*!
     * \brief Координаты конечного элемента ребра.
     */
    QPointF destPoint;
    /*!
     * \brief Размер указателя стрелки при отрисовке.
     */
    qreal arrowSize;
};

#endif // EDGE_H
