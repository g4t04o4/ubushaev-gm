#include "exporter.h"

#include <QFile>
#include <QTextStream>

void Exporter::exportToPNG(QPixmap *inpPixmap, QString filename)
{
    inpPixmap->save(filename);
}

void Exporter::exportToTXT(const QString& inpReport, QString filename)
{
    QFile file(filename);
    file.resize(0);
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream << inpReport << endl;
    }
}
