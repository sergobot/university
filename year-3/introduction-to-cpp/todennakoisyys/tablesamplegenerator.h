#ifndef TABLESAMPLEGENERATOR_H
#define TABLESAMPLEGENERATOR_H

#include "samplegenerator.h"

class TableSampleGenerator : public SampleGenerator
{
    Q_OBJECT
public:
    TableSampleGenerator(QObject *parent);

    virtual Sample generate(Distribution*, size_t size);
};

#endif // TABLESAMPLEGENERATOR_H
