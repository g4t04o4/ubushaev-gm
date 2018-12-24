#include "exporter.h"

#include <QFile>
#include <QTextStream>

void Exporter::exportToPNG(QPixmap *inputPixmap, QString filename)
{
    inputPixmap->save(filename);
}

void Exporter::exportToTXT(const QString& inputReport, QString filename)
{
    QFile file(filename);
    file.resize(0);
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream << inputReport << endl;
    }
}
