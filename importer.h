#ifndef IMPORTER_H
#define IMPORTER_H

#include <QVector>
#include "edgedata.h"

class Importer
{
public:
    int importFromTXT(QVector<EdgeData *>& edgeHeap, const QString& inpFile);
};

#endif // IMPORTER_H
