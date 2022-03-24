#ifndef SAMPLEGENERATOR_H
#define SAMPLEGENERATOR_H

#include <QObject>

#include "distribution.h"
#include "sample.h"

class SampleGenerator : public QObject
{
    Q_OBJECT
public:
    explicit SampleGenerator(QObject *parent = nullptr);
    virtual ~SampleGenerator() {};

    virtual Sample generate(const Distribution, size_t size);
};

#endif // SAMPLEGENERATOR_H
