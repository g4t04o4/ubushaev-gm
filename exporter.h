#ifndef EXPORTER_H
#define EXPORTER_H

#include <QPixmap>
#include <QString>

class Exporter
{
public:
    void exportToPNG(QPixmap *inpPixmap, QString filename);
    void exportToTXT(const QString& inpReport, QString filename);
};

#endif // EXPORTER_H
