#ifndef EXPORTER_H
#define EXPORTER_H

#include <QPixmap>
#include <QString>

/*!
 * \brief Класс для экспорта данных из программы.
 */
class Exporter
{
public:
    /*!
     * \brief Метод, экспортирующий текущее состояние виджета, содержащего граф, в PNG формат.
     * \param inpPixmap - изображение виджета-графа.
     * \param filename - адрес места сохранения изображения.
     */
    void exportToPNG(QPixmap *inputPixmap, QString filename);
    /*!
     * \brief Метод экспортирующий структуру графа (не текущее состояние, а лишь структуру) в кастомный TXT формат.
     * \param inputReport - собственно, полученная от графа информация о его структуре.
     * \param filename - адрес места сохранения текстового файла.
     */
    void exportToTXT(const QString& inputReport, QString filename);
};

#endif // EXPORTER_H
