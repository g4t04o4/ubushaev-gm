#ifndef EDGEDATA_H
#define EDGEDATA_H

/*!
 * \brief Класс, содержащий данные о рёбре. Необходим для импорта.
 */
class EdgeData
{
public:
    /*!
     * \brief Конструктор для данных ребра.
     * \param _src - номер начального элемента.
     * \param _dest - номер конечного элемента.
     */
    EdgeData(unsigned int _src,unsigned int _dest):
        src(_src),
        dest(_dest)
    {}
    /*!
     * \brief номер начального элемента.
     */
    unsigned int src;
    /*!
     * \brief номер конечного элемента.
     */
    unsigned int dest;
};
#endif // EDGEDATA_H
