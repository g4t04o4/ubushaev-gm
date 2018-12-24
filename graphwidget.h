#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>

class Node;
class Edge;
class Exporter;

/*!
 * \brief Виджет на основе QGraphicsView, содержащий граф.
 */
class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:

    /*!
     * \brief Конструктор виджета.
     */
    GraphWidget(QWidget *parent = nullptr);

    /*!
     * \brief Метод следит за передвижением элементов графа и запускает/останавливает таймер по необходимости.
     */
    void itemMoved();


public slots:
    /*!
     * \brief Заполнение графа заданным количеством элементов и рёбер.
     * \param nodeCount - количество элементов графа.
     * \param edgeCount - максимальное количество рёбер в этом графе.
     */
    void fillGraph(int nodeCount, int edgeCount);

    /*!
     * \brief Метод для перетасовки наугад элементов графа.
     */
    void shuffle();

    /*!
     * \brief Метод масштабирования. Увеличивает масштаб изображения.
     */
    void zoomIn();

    /*!
     * \brief Метод масштабирования. Уменьшает масштаб изображения.
     */
    void zoomOut();

    /*!
     * \brief Останавливает симуляцию.
     */
    void pause();

    /*!
     * \brief Метод, передающий экспортёру изображение графа.
     * \param filename - полученный от пользователя путь сохранения изображения.
     */
    void exportToPNG(QString filename);

    /*!
     * \brief Метод, создающий краткое описание структуры графа и передающий его экспортёру.
     * \param filename - полученный от пользователя путь сохранения структуры графа.
     */
    void exportToTXT(QString filename);

    /*!
     * \brief Метод, создающий модель графа по полученным от импортёра инструкциям.
     * \param inputFilePath - полученный от пользователя адрес файла с описанием структуры графа.
     */
    void openGraphFromTXT(QString inputFilePath);

    /*!
     * \brief Метод очистки сцены от графа.
     */
    void clearScreen();

    /*!
     * \brief Метод пересоздаёт рандомный граф.
     */
    void recreate();

protected:

    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    /*!
     * \brief Отрисовка фона виджета.
     */
    void drawBackground(QPainter *painter,
                        const QRectF &rect) override;

    /*!
     * \brief Метод, необходимый для корректного масштабирования.
     * \param scaleFactor - коэффициент масштабирования виджета.
     */
    void scaleView(qreal scaleFactor);

private:
    /*!
     * \brief Счётчик элементов графа. Необходим для задания свежесозданным элементам порядковых номеров.
     */
    unsigned int lastNodeID;

    /*!
     * \brief Сцена, содержащая составляющие графа.
     */
    QGraphicsScene *scene = new QGraphicsScene(this);

    /*!
     * \brief Вектор, содержащий указатели на элементы графа.
     */
    QVector<Node *> nodeVector;

    /*!
     * \brief Вектор, содержащий указатели на рёбра графа.
     */
    QVector<Edge *> edgeVector;

    /*!
     * \brief Таймер для симуляции графа.
     */
    int timerId;

    /*!
     * \brief Количество элементов в графе.
     */
    int nodeCount;

    /*!
     * \brief Количество рёбер в графе.
     */
    int edgeCount;

    /*!
     * \brief Главный узел графа. Именно он двигается с помощью клавиатуры.
     */
    Node *leaderNode;

    /*!
     * \brief Размер виджета.
     */
    int wsize;

    /*!
     * \brief Флаг для остановки симуляции.
     */
    bool pauseflag;
};

#endif // GRAPHWIDGET_H
