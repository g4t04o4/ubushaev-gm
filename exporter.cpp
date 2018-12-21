#include "exporter.h"

#include <QFile>
#include <QTextStream>
#include <QFileDialog>

Exporter::Exporter()
{
}

void Exporter::exportToPNG(QPixmap *inpPixmap, QString filename)
{
    inpPixmap->save(filename);
}

void Exporter::exportToTXT(QString *inpReport, QString filename)
{
    QFile file(filename);
    file.resize(0);
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream << inpReport << endl;
    }
}
