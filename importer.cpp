#include "importer.h"
#include <QFile>
#include <QTextStream>

std::vector<EdgeData> Importer::importFromTXT(const QString& inputFilePath, int &nodeCount)
{
    QFile inputFile(inputFilePath);
    std::vector<EdgeData> edges;

    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);
        QString line = in.readLine();
        nodeCount = (line).toInt();
        line = in.readLine();

        while (!in.atEnd())
        {
            line = in.readLine();
            unsigned int source = 0, dest = 0;
            auto smth = line.split(" ");
            source = smth[0].toUInt();
            dest = smth[1].toUInt();

            edges.emplace_back(EdgeData{source,dest});
        }

        inputFile.close();
    }

    return edges;
}
