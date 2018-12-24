#include "importer.h"
#include <QFile>
#include <QTextStream>

int Importer::importFromTXT(QVector<EdgeData *>& edgeHeap,const QString& inpFile)
{
    QFile inputFile(inpFile);
    int nodeCount = 0,
                 edgeCount = 0;
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       QString line = in.readLine();
       nodeCount = line.toInt();
       line = in.readLine();
       edgeCount = line.toInt();
       while (!in.atEnd())
       {
          line = in.readLine();
          unsigned int source = 0, dest = 0;
          auto smth = line.split(" ");
          source = smth[0].toUInt();
          dest = smth[1].toUInt();
          edgeHeap.append(new EdgeData(source,dest));
       }
       inputFile.close();
    }
    return nodeCount;
}
