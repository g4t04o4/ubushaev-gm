#ifndef EXPORTER_H
#define EXPORTER_H

#include <QPixmap>
#include <QString>

class Exporter
{
public:
    Exporter();
    void exportToPNG(QPixmap *inpPixmap, QString filename);
    void exportToTXT(QString *inpReport, QString filename);
};

#endif // EXPORTER_H
