#ifndef IMPORTER_H
#define IMPORTER_H

#include <QVector>
#include "edgedata.h"

class Importer
{
public:
    std::vector<EdgeData> importFromTXT(const QString& inpFile);
};

#endif // IMPORTER_H
