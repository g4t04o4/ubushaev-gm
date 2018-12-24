#ifndef IMPORTER_H
#define IMPORTER_H

#include <QVector>
#include "edgedata.h"

/*!
 * \brief Класс для импорта информации о графе. Необходимо для дальнейшего воссоздания графа.
 */
class Importer
{
public:
    /*!
     * \brief Импорт информации о структуре графа из стороннего TXT файла и последующее создание понятной виджету информации о графе.
     * \param inputFilePath - полученный от пользователя адрес файла с описанием структуры графа.
     * \param nodeCount - ссылка на счётчик элементов виджета.
     * \return вектор с данными о рёбрах графа.
     */
    std::vector<EdgeData> importFromTXT(const QString& inputFilePath, int &nodeCount);
};

#endif // IMPORTER_H
