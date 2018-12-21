#ifndef EDGEDATA_H
#define EDGEDATA_H

class EdgeData
{
public:
    EdgeData(unsigned int _src,unsigned int _dest):
        src(_src),
        dest(_dest)
    {}
    unsigned int src;
    unsigned int dest;
};
#endif // EDGEDATA_H
